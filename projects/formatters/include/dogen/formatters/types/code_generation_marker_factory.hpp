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
#ifndef DOGEN_FORMATTERS_TYPES_CODE_GENERATION_MARKER_FACTORY_HPP
#define DOGEN_FORMATTERS_TYPES_CODE_GENERATION_MARKER_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace formatters {

class code_generation_marker_factory {
public:
    code_generation_marker_factory(
        const code_generation_marker_factory&) = default;
    code_generation_marker_factory(code_generation_marker_factory&&) = default;
    code_generation_marker_factory& operator=(
        const code_generation_marker_factory&) = default;

public:
    code_generation_marker_factory();
    code_generation_marker_factory(const bool add_date_time,
        const bool add_warning, const std::string& message);

    std::string build() const;

private:
    const bool add_date_time_;
    const bool add_warning_;
    const std::string message_;
};

} }

#endif
