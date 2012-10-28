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
#include "dogen/comments/test_data/multi_line_td.hpp"
#include "dogen/comments/test_data/versioned_key_td.hpp"

namespace {

dogen::comments::versioned_key
create_dogen_comments_versioned_key(const unsigned int position) {
    return dogen::comments::versioned_key_generator::create(position);
}

}

namespace dogen {
namespace comments {

multi_line_generator::multi_line_generator() : position_(0) { }

void multi_line_generator::
populate(const unsigned int position, result_type& v) {
    v.versioned_key(create_dogen_comments_versioned_key(position + 0));
}

multi_line_generator::result_type
multi_line_generator::create(const unsigned int position) {
    multi_line r;
    multi_line_generator::populate(position, r);
    return r;
}

multi_line_generator::result_type
multi_line_generator::operator()() {
    return create(position_++);
}

} }