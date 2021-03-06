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
#include <ostream>
#include "dogen/cpp/io/cpp_settings_io.hpp"
#include "dogen/cpp/io/facet_settings_io.hpp"
#include "dogen/cpp/io/formatter_settings_io.hpp"
#include "dogen/cpp/io/global_settings_io.hpp"
#include "dogen/formatters/io/general_settings_io.hpp"

namespace dogen {
namespace cpp {

std::ostream& operator<<(std::ostream& s, const global_settings& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::global_settings\"" << ", "
      << "\"facet_settings\": " << v.facet_settings() << ", "
      << "\"cpp_settings\": " << v.cpp_settings() << ", "
      << "\"formatter_settings\": " << v.formatter_settings() << ", "
      << "\"general_settings\": " << v.general_settings()
      << " }";
    return(s);
}

} }