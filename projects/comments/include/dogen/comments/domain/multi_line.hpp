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
#ifndef DOGEN_COMMENTS_DOMAIN_MULTI_LINE_HPP
#define DOGEN_COMMENTS_DOMAIN_MULTI_LINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/comments/domain/versioned_key.hpp"
#include "dogen/comments/serialization/multi_line_fwd_ser.hpp"

namespace dogen {
namespace comments {

/*
 * @brief first line
 *
 * second line
 */
class multi_line final {
public:
    multi_line() = default;
    multi_line(const multi_line&) = default;
    multi_line(multi_line&&) = default;
    ~multi_line() = default;

public:
    explicit multi_line(const dogen::comments::versioned_key& versioned_key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const multi_line& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, multi_line& v, unsigned int version);

public:
    dogen::comments::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(const dogen::comments::versioned_key& v) {
        versioned_key_ = v;
    }

public:
    bool operator==(const multi_line& rhs) const;
    bool operator!=(const multi_line& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(multi_line& other) noexcept;
    multi_line& operator=(multi_line other);

private:
    dogen::comments::versioned_key versioned_key_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::comments::multi_line& lhs,
    dogen::comments::multi_line& rhs) {
    lhs.swap(rhs);
}

}

#endif