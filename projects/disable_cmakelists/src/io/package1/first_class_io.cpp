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
#include "dogen/disable_cmakelists/io/package1/first_class_io.hpp"
#include "dogen/disable_cmakelists/io/versioned_key_io.hpp"

namespace dogen {
namespace disable_cmakelists {
namespace package1 {

std::ostream& operator<<(std::ostream& stream, first_class value) {
    stream << " { "
           << "\"__type__\": " << "\"first_class\"" << ", "
           << "\"public_attribute\": " << value.public_attribute() << ", "
           << "\"private_attribute\": " << value.private_attribute() << ", "
           << "\"versioned_key\": " << value.versioned_key()
           << " }";
    return(stream);
}

} } }