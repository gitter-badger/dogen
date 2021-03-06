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
#include "dogen/test_models/stereotypes/io/pkg1/keyed_in_package_io.hpp"

namespace dogen {
namespace test_models {
namespace stereotypes {
namespace pkg1 {

std::ostream& operator<<(std::ostream& s, const keyed_in_package& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::stereotypes::pkg1::keyed_in_package\"" << ", "
      << "\"prop_0\": " << v.prop_0()
      << " }";
    return(s);
}

} } } }