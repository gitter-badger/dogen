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
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include "dogen/cpp/serialization/specialized_property_sheet_ser.hpp"


namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::cpp::specialized_property_sheet& v,
    const unsigned int /*version*/) {
    ar << make_nvp("generate_header_guards", v.generate_header_guards_);
    ar << make_nvp("split_project", v.split_project_);
    ar << make_nvp("source_directory", v.source_directory_);
    ar << make_nvp("include_directory", v.include_directory_);
    ar << make_nvp("header_file_extension", v.header_file_extension_);
    ar << make_nvp("implementation_file_extension", v.implementation_file_extension_);
    ar << make_nvp("forward_declaration_postfix", v.forward_declaration_postfix_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::cpp::specialized_property_sheet& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("generate_header_guards", v.generate_header_guards_);
    ar >> make_nvp("split_project", v.split_project_);
    ar >> make_nvp("source_directory", v.source_directory_);
    ar >> make_nvp("include_directory", v.include_directory_);
    ar >> make_nvp("header_file_extension", v.header_file_extension_);
    ar >> make_nvp("implementation_file_extension", v.implementation_file_extension_);
    ar >> make_nvp("forward_declaration_postfix", v.forward_declaration_postfix_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::cpp::specialized_property_sheet& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::cpp::specialized_property_sheet& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::cpp::specialized_property_sheet& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::cpp::specialized_property_sheet& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::cpp::specialized_property_sheet& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::cpp::specialized_property_sheet& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::cpp::specialized_property_sheet& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::cpp::specialized_property_sheet& v, unsigned int version);

} }