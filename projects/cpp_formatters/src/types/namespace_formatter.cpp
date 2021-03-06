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
#include <ostream>
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"

namespace dogen {
namespace cpp_formatters {

namespace_formatter::namespace_formatter(std::ostream& stream)
    : stream_(stream) { }

void namespace_formatter::format_start(const std::string& name) {
    stream_ << "namespace";
    if (name.empty())
        stream_ << " {";
    else
        stream_ << " " << name << " {";
    stream_ << std::endl;
}

void namespace_formatter::format_end() {
    stream_ << "}"; // no std::endl by design
}

} }
