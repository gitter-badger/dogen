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
#ifndef DOGEN_CPP_TYPES_FORMATTER_SETTINGS_HPP
#define DOGEN_CPP_TYPES_FORMATTER_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/cpp/serialization/formatter_settings_fwd_ser.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Settings pertaining to a given formatter, but that are common to all formatters.
 */
class formatter_settings final {
public:
    formatter_settings(const formatter_settings&) = default;
    formatter_settings(formatter_settings&&) = default;
    ~formatter_settings() = default;

public:
    formatter_settings();

public:
    formatter_settings(
        const bool enabled,
        const std::string& postfix);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const formatter_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, formatter_settings& v, unsigned int version);

public:
    /**
     * @brief If true the formatter will attempt to generate code.
     */
    /**@{*/
    bool enabled() const;
    void enabled(const bool v);
    /**@}*/

    /**
     * @brief Formatter specific postfix to apply to file name, if any.
     */
    /**@{*/
    const std::string& postfix() const;
    std::string& postfix();
    void postfix(const std::string& v);
    void postfix(const std::string&& v);
    /**@}*/

public:
    bool operator==(const formatter_settings& rhs) const;
    bool operator!=(const formatter_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(formatter_settings& other) noexcept;
    formatter_settings& operator=(formatter_settings other);

private:
    bool enabled_;
    std::string postfix_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::formatter_settings& lhs,
    dogen::cpp::formatter_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
