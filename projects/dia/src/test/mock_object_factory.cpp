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
#include <string>
#include <boost/lexical_cast.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia/types/connection.hpp"
#include "dogen/dia/types/child_node.hpp"
#include "dogen/dia/test/mock_object_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia.mock_object_factory"));

const std::string empty;
const std::string object_prefix("O");
const std::string uml_large_package("UML - LargePackage");
const std::string uml_class("UML - Class");
const std::string uml_generalization("UML - Generalization");
const std::string uml_association("UML - Association");
const std::string uml_note("UML - Note");
const std::string uml_message("UML - Message");
const std::string uml_realization("UML - Realizes");
const std::string dia_stereotype("stereotype");
const std::string dia_name("name");
const std::string enumeration_stereotype("#enumeration#");
const std::string invalid_stereotype("Invalid stereotype: ");

dogen::dia::attribute
create_string_attribute(const std::string& name, const std::string& value) {
    dogen::dia::attribute r;
    r.name(name);

    dogen::dia::string v;
    v.value(value);
    r.values().push_back(v);

    return r;
}

dogen::dia::object
create_object(const std::string& type, const unsigned int number) {
    dogen::dia::object r;
    r.id(dogen::dia::test::mock_object_factory::to_oject_id(number));
    r.type(type);
    return r;
}

void create_name_attribute(dogen::dia::object& o, const std::string& value) {
    std::ostringstream s;
    s << "#" << value << "#";
    o.attributes().push_back(create_string_attribute(dia_name, s.str()));
}

void create_name_attribute(dogen::dia::object& o, const unsigned int number) {
    std::ostringstream s;
    s << "name_" << number;
    create_name_attribute(o, s.str());
}

void create_stereotype_attribute(dogen::dia::object& o, const std::string st) {
    o.attributes().push_back(create_string_attribute(dia_stereotype, st));
}

dogen::dia::object
create_named_object(const std::string& type, const unsigned int number) {
    dogen::dia::object r(create_object(type, number));
    create_name_attribute(r, number);
    return r;
}

dogen::dia::connection create_connection(const std::string& id) {
    dogen::dia::connection r;
    r.to(id);
    return r;
}

}

namespace dogen {
namespace dia {
namespace test {

std::string mock_object_factory::to_oject_id(const unsigned int number) {
    return object_prefix + boost::lexical_cast<std::string>(number);
}

object mock_object_factory::build_class(const unsigned int number) {
    object r(create_named_object(uml_class, number));
    create_stereotype_attribute(r, empty);
    return r;
}

object mock_object_factory::build_no_name_class(const unsigned int number) {
    object r(create_object(uml_class, number));
    create_stereotype_attribute(r, empty);
    return r;
}

object mock_object_factory::build_blank_name_class(const unsigned int number) {
    object r(create_object(uml_class, number));
    create_stereotype_attribute(r, empty);
    create_name_attribute(r, empty);
    return r;
}

object mock_object_factory::build_large_package(const unsigned int number) {
    return create_named_object(uml_large_package, number);
}

std::array<object, 2> mock_object_factory::
build_class_inside_large_package(unsigned int number)  {
    std::array<object, 2> r = {{
            build_large_package(number),
            build_class(++number),
        }};

    const child_node cn(r[0].id());
    r[1].child_node(cn);
    return r;
}

std::array<object, 3> mock_object_factory::
build_class_inside_two_large_packages(unsigned int number)  {
    std::array<object, 3> r = {{
            build_large_package(number),
            build_large_package(++number),
            build_class(++number),
        }};

    const child_node cn(r[0].id());
    r[1].child_node(cn);

    const child_node cn2(r[1].id());
    r[2].child_node(cn2);

    return r;
}

object mock_object_factory::build_stereotyped_class(
    const std::string& st, const unsigned int number) {
    object r(create_named_object(uml_class, number));
    create_stereotype_attribute(r, st);
    return r;
}

std::array<object, 3>
mock_object_factory::build_generalization(unsigned int number) {
    std::array<object, 3> r = {{
        create_object(uml_class, number),
        build_class(++number),
        create_object(uml_generalization, ++number)
        }};

    r[2].connections(
        std::vector<connection> {
            create_connection(r[0].id()), create_connection(r[1].id())});

    return r;
}

std::array<object, 3>
mock_object_factory::build_association(unsigned int number) {
    std::array<object, 3> r = {{
            build_class(number),
            build_class(++number),
            create_object(uml_association, ++number)
        }};

    r[2].connections(
        std::vector<connection> {
            create_connection(r[0].id()), create_connection(r[1].id())});

    return r;
}

std::array<object, 4> mock_object_factory::
build_generalization_inside_large_package(unsigned int number)  {
    std::array<object, 4> r = {{
            build_large_package(number),
            build_class(++number),
            build_class(++number),
            create_object(uml_generalization, ++number)
        }};

    r[3].connections(
        std::vector<connection> {
            create_connection(r[1].id()), create_connection(r[2].id())});

    const child_node cn(r[0].id());
    r[1].child_node(cn);
    r[2].child_node(cn);
    r[3].child_node(cn);

    return r;
}

std::array<object, 4> mock_object_factory::
build_first_degree_cycle(unsigned int number) {
    std::array<object, 4> r = {{
            build_class(++number),
            build_class(++number),
            create_object(uml_generalization, ++number),
            create_object(uml_generalization, ++number)
        }};

    r[2].connections(
        std::vector<connection> {
            create_connection(r[0].id()), create_connection(r[1].id())});

    r[3].connections(
        std::vector<connection> {
            create_connection(r[1].id()), create_connection(r[0].id())});

    return r;
}


} } }
