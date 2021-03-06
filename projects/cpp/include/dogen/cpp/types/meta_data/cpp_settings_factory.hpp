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
#ifndef DOGEN_CPP_TYPES_META_DATA_CPP_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_META_DATA_CPP_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/property_tree/ptree.hpp>
#include "dogen/cpp/types/cpp_settings.hpp"

namespace dogen {
namespace cpp {
namespace meta_data {

/**
 * @brief Generates the C++ settings from meta-data.
 */
class cpp_settings_factory {
public:
    cpp_settings_factory() = default;
    cpp_settings_factory(const cpp_settings_factory&) = default;
    cpp_settings_factory(cpp_settings_factory&&) = default;
    ~cpp_settings_factory() = default;

private:
    /**
     * @brief Returns a default value version of the C++ settings.
     */
    cpp_settings create_default_settings() const;

public:
    /**
     * @brief Given the supplied meta-data, returns the corresponding
     * C++ settings. The missing values are defaulted.
     */
    cpp_settings build(const boost::property_tree::ptree& meta_data) const;
};

} } }

#endif
