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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_FORMATTER_INTERFACE_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_FORMATTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/qname.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/cpp/types/global_settings.hpp"
#include "dogen/cpp/types/includes_builder_interface.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class formatter_interface {
public:
    formatter_interface() = default;
    formatter_interface(const formatter_interface&) = delete;
    formatter_interface(formatter_interface&&) = default;
    virtual ~formatter_interface() noexcept = 0;

public:
    /**
     * @brief Unique identifier for the facet.
     */
    virtual std::string facet_id() const = 0;

    /**
     * @brief Unique identifier for the formatter.
     */
    virtual std::string formatter_id() const = 0;

    /**
     * @brief Create the file name for this formatter, given a
     * qualified name and the current settings.
     */
    virtual boost::filesystem::path
    make_file_name(const global_settings& gs, const sml::qname& qn) const = 0;

    /**
     * @brief Creates an instance of the path spec builder for this
     * formatter.
     */
    virtual std::shared_ptr<includes_builder_interface>
    make_includes_builder() const = 0;
};

} } }

#endif
