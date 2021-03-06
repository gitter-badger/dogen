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
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree_serialization.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/string.hpp>
#include "dogen/sml/serialization/concept_ser.hpp"
#include "dogen/sml/serialization/generation_types_ser.hpp"
#include "dogen/sml/serialization/operation_ser.hpp"
#include "dogen/sml/serialization/origin_types_ser.hpp"
#include "dogen/sml/serialization/property_ser.hpp"
#include "dogen/sml/serialization/qname_ser.hpp"
#include "dogen/utility/serialization/unordered_map.hpp"


namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::sml::concept& v,
    const unsigned int /*version*/) {
    ar << make_nvp("all_properties", v.all_properties_);
    ar << make_nvp("local_properties", v.local_properties_);
    ar << make_nvp("inherited_properties", v.inherited_properties_);
    ar << make_nvp("documentation", v.documentation_);
    ar << make_nvp("meta_data", v.meta_data_);
    ar << make_nvp("name", v.name_);
    ar << make_nvp("generation_type", v.generation_type_);
    ar << make_nvp("origin_type", v.origin_type_);
    ar << make_nvp("containing_module", v.containing_module_);
    ar << make_nvp("operations", v.operations_);
    ar << make_nvp("refines", v.refines_);
    ar << make_nvp("is_parent", v.is_parent_);
    ar << make_nvp("is_child", v.is_child_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::sml::concept& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("all_properties", v.all_properties_);
    ar >> make_nvp("local_properties", v.local_properties_);
    ar >> make_nvp("inherited_properties", v.inherited_properties_);
    ar >> make_nvp("documentation", v.documentation_);
    ar >> make_nvp("meta_data", v.meta_data_);
    ar >> make_nvp("name", v.name_);
    ar >> make_nvp("generation_type", v.generation_type_);
    ar >> make_nvp("origin_type", v.origin_type_);
    ar >> make_nvp("containing_module", v.containing_module_);
    ar >> make_nvp("operations", v.operations_);
    ar >> make_nvp("refines", v.refines_);
    ar >> make_nvp("is_parent", v.is_parent_);
    ar >> make_nvp("is_child", v.is_child_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::sml::concept& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::sml::concept& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::sml::concept& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::sml::concept& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::sml::concept& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::sml::concept& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::sml::concept& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::sml::concept& v, unsigned int version);

} }