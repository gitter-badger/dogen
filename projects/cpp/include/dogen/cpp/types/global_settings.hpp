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
#ifndef DOGEN_CPP_TYPES_GLOBAL_SETTINGS_HPP
#define DOGEN_CPP_TYPES_GLOBAL_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/cpp/serialization/global_settings_fwd_ser.hpp"
#include "dogen/cpp/types/cpp_settings.hpp"
#include "dogen/cpp/types/facet_settings.hpp"
#include "dogen/cpp/types/formatter_settings.hpp"
#include "dogen/formatters/types/general_settings.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Settings applicable to all entities.
 */
class global_settings final {
public:
    global_settings() = default;
    global_settings(const global_settings&) = default;
    global_settings(global_settings&&) = default;
    ~global_settings() = default;

public:
    global_settings(
        const dogen::cpp::facet_settings& facet_settings,
        const dogen::cpp::cpp_settings& cpp_settings,
        const dogen::cpp::formatter_settings& formatter_settings,
        const dogen::formatters::general_settings& general_settings);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const global_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, global_settings& v, unsigned int version);

public:
    const dogen::cpp::facet_settings& facet_settings() const;
    dogen::cpp::facet_settings& facet_settings();
    void facet_settings(const dogen::cpp::facet_settings& v);
    void facet_settings(const dogen::cpp::facet_settings&& v);

    const dogen::cpp::cpp_settings& cpp_settings() const;
    dogen::cpp::cpp_settings& cpp_settings();
    void cpp_settings(const dogen::cpp::cpp_settings& v);
    void cpp_settings(const dogen::cpp::cpp_settings&& v);

    const dogen::cpp::formatter_settings& formatter_settings() const;
    dogen::cpp::formatter_settings& formatter_settings();
    void formatter_settings(const dogen::cpp::formatter_settings& v);
    void formatter_settings(const dogen::cpp::formatter_settings&& v);

    const dogen::formatters::general_settings& general_settings() const;
    dogen::formatters::general_settings& general_settings();
    void general_settings(const dogen::formatters::general_settings& v);
    void general_settings(const dogen::formatters::general_settings&& v);

public:
    bool operator==(const global_settings& rhs) const;
    bool operator!=(const global_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(global_settings& other) noexcept;
    global_settings& operator=(global_settings other);

private:
    dogen::cpp::facet_settings facet_settings_;
    dogen::cpp::cpp_settings cpp_settings_;
    dogen::cpp::formatter_settings formatter_settings_;
    dogen::formatters::general_settings general_settings_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::global_settings& lhs,
    dogen::cpp::global_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
