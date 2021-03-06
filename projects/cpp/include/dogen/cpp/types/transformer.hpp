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
#ifndef DOGEN_CPP_TYPES_TRANSFORMER_HPP
#define DOGEN_CPP_TYPES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <tuple>
#include <memory>
#include <unordered_map>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/concept.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/primitive.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/cpp/types/entity.hpp"
#include "dogen/cpp/types/enum_info.hpp"
#include "dogen/cpp/types/concept_info.hpp"
#include "dogen/cpp/types/visitor_info.hpp"
#include "dogen/cpp/types/property_info.hpp"
#include "dogen/cpp/types/exception_info.hpp"
#include "dogen/cpp/types/namespace_info.hpp"
#include "dogen/cpp/types/primitive_info.hpp"
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/file_settings.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Transforms an SML type into its corresponding C++ type.
 */
class transformer {
public:
    typedef std::unordered_map<std::string, file_settings>
    file_settings_by_formatter_type;

public:
    transformer(
        const std::unordered_map<sml::qname,
                                 file_settings_by_formatter_type>&
        file_settings_by_qname_by_formatter_type,
        const sml::model& m);

private:
    /**
     * @brief Populates all properties at the entity base class level.
     */
    void populate_entity_properties(const sml::qname& qn,
        const std::string& documentation, entity& e) const;

private:
    /**
     * @brief Transforms the SML nested qname into a nested type info.
     */
    void to_nested_type_info(const sml::nested_qname& nqn,
        nested_type_info& nti, std::string& complete_name,
        bool& requires_stream_manipulators) const;

    /**
     * @brief Transforms an SML property into a property info.
     *
     * The four Boolean values on the tuple work as follows:
     *
     * @li position 1: if true, the property has a top-level primitive
     * type.
     *
     * @li position 2: if true, the property requires stream
     * manipulators.
     *
     * @li position 3: if true, the property invalidates the compiler
     * generated move constructor.
     *
     * @li position 4: if true, the property invalidates the compiler
     * generated default constructor.
     */
    std::tuple<property_info, bool, bool, bool, bool>
    to_property_info(const sml::property p, const bool is_immutable,
        const bool is_fluent) const;

    /**
     * @brief Transforms an SML property to an enumerator info.
     */
    enumerator_info to_enumerator_info(const sml::enumerator& e) const;

    /**
     * @brief Transforms a SML value containing an enumeration into an
     * enumeration info.
     */
    std::shared_ptr<enum_info> to_enum_info(const sml::enumeration& e) const;

    /**
     * @brief Transforms a SML module into a namespace info.
     */
    std::shared_ptr<namespace_info>
    to_namespace_info(const sml::module& m) const;

    /**
     * @brief Transforms a SML value containing an exception into an
     * exception info.
     */
    std::shared_ptr<exception_info>
    to_exception_info(const sml::object& o) const;

    /**
     * @brief Transform a SML object into a class info.
     *
     * @param ao object to transform.
     */
    std::shared_ptr<class_info> to_class_info(const sml::object& o,
        const class_types ct) const;

    /**
     * @brief Transform a SML object representing a visitor into a
     * visitor info.
     *
     * @pre value object must have a visitor type.
     */
    std::shared_ptr<visitor_info> to_visitor_info(const sml::object& o) const;

public:
    /**
     * @brief Transform an SML enumeration into a C++ entity.
     */
    std::shared_ptr<entity> transform(const sml::enumeration& e) const;

    /**
     * @brief Transform an SML module into a C++ entity.
     */
    std::shared_ptr<entity> transform(const sml::module& m) const;

    /**
     * @brief Transform an SML concept into a C++ entity.
     */
    std::shared_ptr<entity> transform(const sml::concept& c) const;

    /**
     * @brief Transform an SML primitive into a C++ entity.
     */
    std::shared_ptr<entity> transform(const sml::primitive& p) const;

    /**
     * @brief Transform an SML object into a C++ entity.
     */
    std::shared_ptr<entity> transform(const sml::object& o) const;

private:
    const std::unordered_map<sml::qname, file_settings_by_formatter_type>&
    file_settings_by_qname_by_formatter_type_;
    const sml::model& model_;
};

} }

#endif
