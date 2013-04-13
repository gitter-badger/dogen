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
#include <boost/graph/depth_first_search.hpp>
#include "dogen/dia/types/diagram.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/dia_to_sml/types/graph_builder.hpp"
#include "dogen/dia_to_sml/types/context.hpp"
#include "dogen/dia_to_sml/types/visitor.hpp"
#include "dogen/dia_to_sml/types/object_transformer.hpp"
#include "dogen/dia_to_sml/types/identifier_parser.hpp"
#include "dogen/dia_to_sml/types/workflow.hpp"

namespace dogen {
namespace dia_to_sml {

workflow::~workflow() noexcept { }

graph_type workflow::build_graph(const dia::diagram& diagram) const {
    graph_builder b;
    for (const auto& l : diagram.layers()) {
        for (const auto& o : l.objects()) {
            b.add(o);
        }
    }
    b.build();
    return b.graph();
}

void workflow::initialise_context(const std::string& model_name,
    const std::string& external_package_path,
    bool is_target, context& c) const {

    const auto epp(identifier_parser::parse_scoped_name(external_package_path));
    c.external_package_path(epp);
    c.model_name(model_name);
    c.is_target(is_target);
}

void workflow::graph_to_context(const graph_type& g, context& c) const {
    object_transformer t(c);
    visitor v(t);
    boost::depth_first_search(g, boost::visitor(v));
}

void workflow::context_to_model(const context& c, sml::model& m) const {

    for (const auto d : c.dependencies()) {
        sml::reference ref;
        ref.model_name(d);
        m.dependencies().insert(std::make_pair(d, ref));
    }
    m.packages(c.packages());
    m.enumerations(c.enumerations());
    m.pods(c.pods());
    m.exceptions(c.exceptions());
    m.is_system(false);
    m.name(c.model_name());
}

sml::model workflow::execute(const dia::diagram& diagram,
    const std::string& model_name,
    const std::string& external_package_path,
    bool is_target) {

    context c;
    initialise_context(model_name, external_package_path, is_target, c);

    auto g(build_graph(diagram));
    graph_to_context(g, c);

    sml::model r;
    context_to_model(c, r);
    return r;
}

} }