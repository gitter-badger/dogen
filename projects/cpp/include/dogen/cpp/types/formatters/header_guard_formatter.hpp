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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_HEADER_GUARD_FORMATTER_FWD_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_HEADER_GUARD_FORMATTER_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Generates C++ header guards.
 */

class header_guard_formatter {
public:
    header_guard_formatter() = default;
    header_guard_formatter(const header_guard_formatter&) = default;
    header_guard_formatter& operator=(
        const header_guard_formatter&) = delete;
    header_guard_formatter(header_guard_formatter&& rhs) = default;

private:
    /**
     * @brief Converts a relative path to a header file into a C++
     * header guard name.
     */
    std::string to_header_guard_name(const boost::filesystem::path& p) const;

public:
    /**
     * @brief Creates the starting block of the header guard.
     */
    void format_begin(std::ostream& s, const boost::filesystem::path& p);

    /**
     * @brief Creates the ending block of the header guard.
     */
    void format_end(std::ostream& s, const boost::filesystem::path& p);
};

} } }

#endif
