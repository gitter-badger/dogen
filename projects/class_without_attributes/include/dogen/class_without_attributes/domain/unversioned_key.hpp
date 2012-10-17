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
#ifndef DOGEN_CLASS_WITHOUT_ATTRIBUTES_DOMAIN_UNVERSIONED_KEY_HPP
#define DOGEN_CLASS_WITHOUT_ATTRIBUTES_DOMAIN_UNVERSIONED_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace dogen {
namespace class_without_attributes {

class unversioned_key_serializer;

class unversioned_key {
public:
    unversioned_key(const unversioned_key&) = default;
    unversioned_key(unversioned_key&&) = default;
    ~unversioned_key() = default;

public:
    unversioned_key();

public:
    explicit unversioned_key(unsigned int id);

public:
    friend class dogen::class_without_attributes::unversioned_key_serializer;

public:
    unsigned int id() const {
        return id_;
    }

    void id(unsigned int value) {
        id_ = value;
    }

public:
    bool operator==(const unversioned_key& rhs) const;

    bool operator!=(const unversioned_key rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(unversioned_key& other);
    unversioned_key& operator=(unversioned_key other);

private:
    unsigned int id_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::class_without_attributes::unversioned_key& lhs,
    dogen::class_without_attributes::unversioned_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
