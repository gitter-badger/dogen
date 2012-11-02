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
#include "dogen/boost_model/domain/class_base.hpp"
#include "dogen/boost_model/io/versioned_key_io.hpp"

namespace dogen {
namespace boost_model {

class_base::class_base()
    : prop_0_(static_cast<int>(0)) { }

class_base::class_base(
    const int prop_0,
    const dogen::boost_model::versioned_key& versioned_key)
    : prop_0_(prop_0),
      versioned_key_(versioned_key) { }

void class_base::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"class_base\"" << ", "
      << "\"prop_0\": " << prop_0_ << ", "
      << "\"versioned_key\": " << versioned_key_
      << " }";
}

void class_base::swap(class_base& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(versioned_key_, other.versioned_key_);
}

bool class_base::operator==(const class_base& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        versioned_key_ == rhs.versioned_key_;
}

} }