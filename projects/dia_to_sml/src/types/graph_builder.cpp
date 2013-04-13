/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/types/enum_parser.hpp"
#include "dogen/dia_to_sml/types/object_types.hpp"
#include "dogen/dia_to_sml/io/object_types_io.hpp"
#include "dogen/dia_to_sml/types/building_error.hpp"
#include "dogen/dia_to_sml/types/graph_builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.graph_builder"));

/**
 * @brief String representation of the root vertex ID graph.
 */
const std::string root_id("__root__");

// error messages
const std::string error_add_after_build("Cannot add object after building");
const std::string error_not_built("Graph has not yet been built");
const std::string error_parsing_object_type("Fail to parse object type: ");
const std::string unexpected_number_of_connections(
    "Expected 2 connections but found: ");
const std::string relationship_target_not_found(
    "Relationship points to object with non-existent ID: ");
const std::string found_cycle_in_graph("Graph has a cycle: ");

}

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Detects cycles in the graph.
 */
class cycle_detector : public boost::default_dfs_visitor {
private:
    struct state {
        std::ostringstream stream_;
    };

public:
    cycle_detector() : state_(new state()) { }

public:
    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex&, const Graph&) {
        state_->stream_ << ")";
    }

    template<typename Vertex, typename Graph>
    void discover_vertex(const Vertex& u, const Graph& g) {
        state_->stream_ << "(" << g[u].id();
    }

    void back_edge(graph_type::edge_descriptor e, const graph_type& g) {
        state_->stream_ << "(" << g[target(e, g)].id();
        BOOST_LOG_SEV(lg, error) << found_cycle_in_graph
                                 << g[target(e, g)].id() << ". Graph as sexp: "
                                 << state_->stream_.str();

        BOOST_THROW_EXCEPTION(building_error(found_cycle_in_graph +
                boost::lexical_cast<std::string>(g[target(e, g)].id())));
    }

    const std::string sexp() { return state_->stream_.str(); }

private:
    std::shared_ptr<state> state_;
};

graph_builder::graph_builder()
    : built_(false), root_vertex_(boost::add_vertex(graph_)) {
    dia::object root;
    root.id(::root_id);
    graph_[root_vertex_] = root;
    id_to_vertex_.insert(std::make_pair(::root_id, root_vertex_));
}

std::string graph_builder::root_id() {
    return ::root_id;
}

graph_builder::vertex_descriptor_type
graph_builder::vertex_for_id(const std::string& id) {
    const auto i(id_to_vertex_.find(id));
    if (i != id_to_vertex_.end()) {
        BOOST_LOG_SEV(lg, debug) << "Vertex already exists: " << id;
        return i->second;
    }

    const auto r(boost::add_vertex(graph_));
    id_to_vertex_.insert(std::make_pair(id, r));
    BOOST_LOG_SEV(lg, debug) << "Created vertex: " << id;

    return r;
}

void graph_builder::ensure_not_built() const {
    if (built_)
        throw building_error(error_add_after_build);
}

void graph_builder::ensure_built() const {
    if (!built_)
        throw building_error(error_not_built);
}

bool graph_builder::is_relevant(const dia::object& o) const {
    using dia_to_sml::object_types;
    object_types ot(object_types::invalid);

    try {
        using dogen::dia_to_sml::enum_parser;
        ot = enum_parser::parse_object_type(o.type());
    } catch(const std::exception& e) {
        std::ostringstream stream;
        stream << error_parsing_object_type << "'" << o.type()
               << "'. Error: " << e.what();

        BOOST_LOG_SEV(lg, error) << stream.str();
        BOOST_THROW_EXCEPTION(building_error(stream.str()));
    }

    return
        ot == object_types::uml_large_package ||
        ot == object_types::uml_generalization ||
        ot == object_types::uml_class;
}

void graph_builder::
process_child_node(const vertex_descriptor_type& v, const dia::object& o) {
    if (o.child_node()) {
        const std::string id(o.child_node()->parent());
        const vertex_descriptor_type cv(vertex_for_id(id));
        boost::add_edge(cv, v, graph_);
        BOOST_LOG_SEV(lg, debug) << "Creating containing relationship for: "
                                 << o.id() << ". Container ID: " << id;
        return;
    }

    orphanage_.insert(std::make_pair(o.id(), v));
    BOOST_LOG_SEV(lg, debug) << "Vertex for object joined orphanage: "
                             << o.id();
}

void graph_builder::process_connections(const dia::object& o) {
    const auto connections(o.connections());
    if (connections.size() != 2) {
        const auto size(boost::lexical_cast<std::string>(connections.size()));
        BOOST_LOG_SEV(lg, error) << unexpected_number_of_connections << size;
        BOOST_THROW_EXCEPTION(
            building_error(unexpected_number_of_connections + size));
    }

    const auto parent(connections.front());
    const auto child(connections.back());
    BOOST_LOG_SEV(lg, debug) << "Processing connections for object: '"
                             << o.id() << "' of type: '" << o.type() << "'";

    auto lambda([&](const std::string& id) -> vertex_descriptor_type {
            const auto i(id_to_vertex_.find(id));
            if (i == id_to_vertex_.end()) {
                BOOST_LOG_SEV(lg, error) << relationship_target_not_found << id;

                BOOST_THROW_EXCEPTION(
                    building_error(relationship_target_not_found + id));
            }
            return i->second;
        });


    const auto parent_vertex(lambda(parent.to()));
    const auto child_vertex(lambda(child.to()));
    parent_ids_.insert(parent.to());
    BOOST_LOG_SEV(lg, debug) << "Connecting parent '"
                             << parent.to() << "' to child: '"
                             << child.to()
                             << "'";

    boost::add_edge(parent_vertex, child_vertex, graph_);
    const auto pair(std::make_pair(child.to(), parent.to()));
    const bool key_exists(!child_to_parent_.insert(pair).second);

    if (key_exists) {
        std::ostringstream ss;
        ss << "Child has more than one parent: '"
           << child.to() << "'. Multiple inheritance "
           << "is not supported.";

        BOOST_LOG_SEV(lg, error) << ss.str();
        BOOST_THROW_EXCEPTION(building_error(ss.str()));
    }

    const auto k(orphanage_.find(child.to()));
    if (k != orphanage_.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object is no longer orphan: "
                                 << k->first << "'";
        orphanage_.erase(k);
    }
}

void graph_builder::add(const dia::object& o) {
    ensure_not_built();

    if (!is_relevant(o))
        return;

    if (o.connections().empty()) {
        const auto v(vertex_for_id(o.id()));
        graph_[v] = o;
        process_child_node(v, o);
        return;
    }
    process_connections(o);
}

const graph_type& graph_builder::graph() const {
    ensure_built();
    return graph_;
}

const std::unordered_map<std::string, std::string>& graph_builder::
child_to_parent() const {
    ensure_built();
    return child_to_parent_;
}

const std::unordered_set<std::string>& graph_builder::parent_ids() const {
    ensure_built();
    return parent_ids_;
}

void graph_builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Processing orphan vertices.";
    for (const auto& pair : orphanage_) {
        BOOST_LOG_SEV(lg, debug) << "Connecting root to '" << pair.first << "'";
        boost::add_edge(root_vertex_, pair.second, graph_);
    }

    cycle_detector v;
    boost::depth_first_search(graph_, boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << "Graph has no cycles. Sexp: " << v.sexp();
    built_ = true;
}

} }