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
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/xml_serialization_helper.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/utility/test_data/codegen_tds.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/dia/types/hydrator.hpp"
#include "dogen/dia_to_sml/types/transformer.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::dia_to_sml;
using dogen::utility::test::asserter;

namespace  {

const std::string test_module("dia_to_sml");
const std::string test_suite("transformer_spec");

bool test_transformer(
    boost::filesystem::path input_path,
    boost::filesystem::path expected_path,
    boost::filesystem::path actual_path) {

    using dogen::utility::test::xml_deserialize;
    const auto input(xml_deserialize<dogen::dia::diagram>(input_path));

    const std::string epp;
    const bool is_target(true);
    const bool verbose(true);
    const std::string model_name(input_path.stem().string());

    transformer t(input, model_name, epp, is_target, verbose);
    dogen::sml::model actual(t.transform());
    return asserter::assert_object(expected_path, actual_path, actual);
}

}

using dogen::utility::test_data::dia_sml;
using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(transformer)

BOOST_AUTO_TEST_CASE(class_in_a_package_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("class_in_a_package_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_class_in_a_package_dia_xml());
    const auto actual_path(dia_sml::actual_class_in_a_package_sml_xml());
    const auto expected_path(dia_sml::expected_class_in_a_package_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_CASE(empty_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("empty_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_empty_dia_xml());
    const auto actual_path(dia_sml::actual_empty_sml_xml());
    const auto expected_path(dia_sml::expected_empty_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_CASE(empty_package_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("empty_package_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_empty_package_dia_xml());
    const auto actual_path(dia_sml::actual_empty_package_sml_xml());
    const auto expected_path(dia_sml::expected_empty_package_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_CASE(classes_inout_package_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("classes_inout_package_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_classes_inout_package_dia_xml());
    const auto actual_path(dia_sml::actual_classes_inout_package_sml_xml());
    const auto expected_path(dia_sml::expected_classes_inout_package_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_CASE(class_without_attributes_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("class_without_attributes_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_class_without_attributes_dia_xml());
    const auto actual_path(dia_sml::actual_class_without_attributes_sml_xml());
    const auto expected_path(dia_sml::expected_class_without_attributes_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_CASE(class_without_package_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("class_without_package_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_class_without_package_dia_xml());
    const auto actual_path(dia_sml::actual_class_without_package_sml_xml());
    const auto expected_path(dia_sml::expected_class_without_package_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_CASE(classes_without_package_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("classes_without_package_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_classes_without_package_dia_xml());
    const auto actual_path(dia_sml::actual_classes_without_package_sml_xml());
    const auto expected_path(dia_sml::expected_classes_without_package_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_CASE(two_layers_with_objects_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("two_layers_with_objects_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_two_layers_with_objects_dia_xml());
    const auto actual_path(dia_sml::actual_two_layers_with_objects_sml_xml());
    const auto expected_path(dia_sml::expected_two_layers_with_objects_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_CASE(all_primitives_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("all_primitives_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_all_primitives_dia_xml());
    const auto actual_path(dia_sml::actual_all_primitives_sml_xml());
    const auto expected_path(dia_sml::expected_all_primitives_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_CASE(trivial_inheritance_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("trivial_inheritance_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_trivial_inheritance_dia_xml());
    const auto actual_path(dia_sml::actual_trivial_inheritance_sml_xml());
    const auto expected_path(dia_sml::expected_trivial_inheritance_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_CASE(std_model_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("std_model_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_std_model_dia_xml());
    const auto actual_path(dia_sml::actual_std_model_sml_xml());
    const auto expected_path(dia_sml::expected_std_model_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_CASE(boost_model_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("boost_model_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_boost_model_dia_xml());
    const auto actual_path(dia_sml::actual_boost_model_sml_xml());
    const auto expected_path(dia_sml::expected_boost_model_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_CASE(comments_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("comments_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_comments_dia_xml());
    const auto actual_path(dia_sml::actual_comments_sml_xml());
    const auto expected_path(dia_sml::expected_comments_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_SUITE_END()