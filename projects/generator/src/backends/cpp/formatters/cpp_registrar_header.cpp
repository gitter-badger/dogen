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
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_registrar_header.hpp"

namespace {

const bool is_system(true);
const bool is_user(false);

const std::string expected_registrar_view_model(
    "File view model must contain a registrar view model");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

registrar_header::
registrar_header(std::ostream& stream) :
    stream_(stream), utility_(stream_, indenter_) { }

file_formatter::shared_ptr registrar_header::
create(std::ostream& stream) {
    return file_formatter::shared_ptr(new registrar_header(stream));
}

void registrar_header::format(const file_view_model& vm) {
    const auto o(vm.registrar_vm());
    if (!o)
        throw generation_failure(expected_registrar_view_model);

    licence licence(stream_);
    licence.format();

    const bool blank_line(false);
    cpp_includes includes(stream_, blank_line);
    includes.format(vm);

    {
        const auto rvm(*o);
        namespace_helper ns(stream_, rvm.namespaces());
        utility_.blank_line();
        stream_ << indenter_ << "template<typename Archive>" << std::endl
                << indenter_ << "void register_types(Archive& ar);"
                << std::endl;
        utility_.blank_line();
    }
    utility_.blank_line();
}

} } } } }