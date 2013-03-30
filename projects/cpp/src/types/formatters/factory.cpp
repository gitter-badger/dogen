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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/config/io/cpp_facet_types_io.hpp"
#include "dogen/cpp/io/file_types_io.hpp"
#include "dogen/cpp/io/aspect_types_io.hpp"
#include "dogen/cpp/types/formatters/production_failure.hpp"
#include "dogen/cpp/types/formatters/facet_includer.hpp"
#include "dogen/cpp/types/formatters/domain_header.hpp"
#include "dogen/cpp/types/formatters/domain_implementation.hpp"
#include "dogen/cpp/types/formatters/facet_includer.hpp"
#include "dogen/cpp/types/formatters/hash_header.hpp"
#include "dogen/cpp/types/formatters/hash_implementation.hpp"
#include "dogen/cpp/types/formatters/io_header.hpp"
#include "dogen/cpp/types/formatters/io_implementation.hpp"
#include "dogen/cpp/types/formatters/generator_header.hpp"
#include "dogen/cpp/types/formatters/generator_implementation.hpp"
#include "dogen/cpp/types/formatters/serialization_header.hpp"
#include "dogen/cpp/types/formatters/serialization_implementation.hpp"
#include "dogen/cpp/types/formatters/registrar_header.hpp"
#include "dogen/cpp/types/formatters/registrar_implementation.hpp"
#include "dogen/cpp/types/formatters/forward_declarations_header.hpp"
#include "dogen/cpp/types/formatters/null_formatter.hpp"
#include "dogen/cpp/types/formatters/odb_header.hpp"
#include "dogen/cpp/types/formatters/factory.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.factory"));
const std::string production_failure_msg("Formatter factory not setup for: ");

bool contains(const std::set<dogen::config::cpp_facet_types>& f,
    dogen::config::cpp_facet_types ft) {
    return f.find(ft) != f.end();
}

}

namespace dogen {
namespace cpp {
namespace formatters {

factory::factory(const config::cpp_settings& settings)
    : settings_(settings),
      disable_io_(!contains(settings_.enabled_facets(),
              config::cpp_facet_types::io)),
      disable_serialization_(!contains(settings_.enabled_facets(),
              config::cpp_facet_types::serialization)) { }

factory::result_type
factory::create_main_formatter(std::ostream& s, config::cpp_facet_types ft,
    file_types flt) const {

    using config::cpp_facet_types;
    switch (ft) {
    case cpp_facet_types::types:
        if (flt == file_types::header)
            return domain_header::create(s,
                settings_.disable_complete_constructor(),
                settings_.use_integrated_io(),
                disable_io_, disable_serialization_);
        else
            return domain_implementation::create(s,
                settings_.disable_complete_constructor(),
                settings_.use_integrated_io(),
                disable_io_);
        break;
    case cpp_facet_types::io:
        if (flt == file_types::header)
            return io_header::create(s);
        else
            return io_implementation::create(s);
        break;
    case cpp_facet_types::hash:
        if (flt == file_types::header)
            return hash_header::create(s);
        else
            return hash_implementation::create(s);
        break;
    case cpp_facet_types::serialization:
        if (flt == file_types::header)
            return serialization_header::create(s,
                settings_.disable_xml_serialization());
        else
            return serialization_implementation::create(s,
                settings_.disable_xml_serialization());
        break;
    case cpp_facet_types::test_data:
        if (flt == file_types::header)
            return generator_header::create(s);
        else
            return generator_implementation::create(s);
        break;
    case cpp_facet_types::odb:
        if (flt == file_types::header)
            return odb_header::create(s);

    default: {
        std::ostringstream s;
        s << production_failure_msg << ft << ", " << flt;
        BOOST_THROW_EXCEPTION(production_failure(s.str()));
    } }
}

factory::result_type factory::create_registrar_formatter(
    std::ostream& s, file_types flt) const {

    switch (flt) {
    case file_types::header:
        return registrar_header::create(s);
        break;

    case file_types::implementation:
        return registrar_implementation::create(s,
            settings_.disable_xml_serialization());
        break;

    default: {
        std::ostringstream ss;
        ss << production_failure_msg << flt;
        BOOST_LOG_SEV(lg, error) << ss.str();
        BOOST_THROW_EXCEPTION(production_failure(ss.str()));
    } }
}

factory::result_type factory::create_null_formatter(std::ostream& s) const {
    return null_formatter::create(s);
}

factory::result_type
factory::create(std::ostream& s, config::cpp_facet_types ft, file_types flt,
    aspect_types at) const {

    switch (at) {
    case aspect_types::main:
        return create_main_formatter(s, ft, flt);
        break;
    case aspect_types::includers:
        return facet_includer::create(s);
        break;
    case aspect_types::forward_decls:
        return forward_declarations_header::create(s);
        break;
    case aspect_types::registrar:
        return create_registrar_formatter(s, flt);
        break;
    case aspect_types::null_aspect:
        return create_null_formatter(s);
        break;
    default: {
        std::ostringstream s;
        s << production_failure_msg << ft << ", " << flt << ", " << at;
        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(production_failure(s.str()));
    } }
}

} } }
