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
#ifndef DOGEN_CONFIG_TYPES_INPUT_SETTINGS_HPP
#define DOGEN_CONFIG_TYPES_INPUT_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <string>
#include <vector>
#include "dogen/config/serialization/input_settings_fwd_ser.hpp"
#include "dogen/config/types/reference.hpp"

namespace dogen {
namespace config {

/**
 * @brief Settings related to the input files.
 */
class input_settings final {
public:
    input_settings(const input_settings&) = default;
    ~input_settings() = default;

public:
    input_settings();

public:
    input_settings(input_settings&& rhs);

public:
    input_settings(
        const boost::filesystem::path& target,
        const std::string& external_module_path,
        const std::vector<dogen::config::reference>& references,
        const bool disable_model_module);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const input_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, input_settings& v, unsigned int version);

public:
    /**
     * @brief Path to the Dia diagram that contains the model to
     *  generate.
     */
    /**@{*/
    const boost::filesystem::path& target() const;
    boost::filesystem::path& target();
    void target(const boost::filesystem::path& v);
    void target(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief External modules which contain the model to generate, delimited by "::".
     */
    /**@{*/
    const std::string& external_module_path() const;
    std::string& external_module_path();
    void external_module_path(const std::string& v);
    void external_module_path(const std::string&& v);
    /**@}*/

    /**
     * @brief All external models in which this model depends.
     */
    /**@{*/
    const std::vector<dogen::config::reference>& references() const;
    std::vector<dogen::config::reference>& references();
    void references(const std::vector<dogen::config::reference>& v);
    void references(const std::vector<dogen::config::reference>&& v);
    /**@}*/

    /**
     * @brief Do not generate a top-level module with the model name.
     */
    /**@{*/
    bool disable_model_module() const;
    void disable_model_module(const bool v);
    /**@}*/

public:
    bool operator==(const input_settings& rhs) const;
    bool operator!=(const input_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(input_settings& other) noexcept;
    input_settings& operator=(input_settings other);

private:
    boost::filesystem::path target_;
    std::string external_module_path_;
    std::vector<dogen::config::reference> references_;
    bool disable_model_module_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::config::input_settings& lhs,
    dogen::config::input_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
