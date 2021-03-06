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
#include "dogen/test_models/classes_without_package/test_data/class_4_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return position;
}

}

namespace dogen {
namespace test_models {
namespace classes_without_package {

class_4_generator::class_4_generator() : position_(0) { }

void class_4_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_int(position + 0));
}

class_4_generator::result_type
class_4_generator::create(const unsigned int position) {
    class_4 r;
    class_4_generator::populate(position, r);
    return r;
}
class_4_generator::result_type*
class_4_generator::create_ptr(const unsigned int position) {
    class_4* p = new class_4();
    class_4_generator::populate(position, *p);
    return p;
}

class_4_generator::result_type
class_4_generator::operator()() {
    return create(position_++);
}

} } }
