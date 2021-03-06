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
#include <stdexcept>
#include "dogen/formatters/io/modeline_locations_io.hpp"

namespace dogen {
namespace formatters {

std::ostream& operator<<(std::ostream& s, const modeline_locations& v) {
    s << "{ " << "\"__type__\": " << "\"modeline_locations\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case modeline_locations::invalid:
        attr = "\"invalid\"";
        break;
    case modeline_locations::top:
        attr = "\"top\"";
        break;
    case modeline_locations::bottom:
        attr = "\"bottom\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for modeline_locations");
    }
    s << attr << " }";
    return s;
}

} }