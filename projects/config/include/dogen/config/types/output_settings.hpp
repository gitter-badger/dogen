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
#ifndef DOGEN_CONFIG_TYPES_OUTPUT_SETTINGS_HPP
#define DOGEN_CONFIG_TYPES_OUTPUT_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include <vector>
#include "dogen/config/serialization/output_settings_fwd_ser.hpp"

namespace dogen {
namespace config {

class output_settings final {
public:
    output_settings(const output_settings&) = default;
    output_settings(output_settings&&) = default;
    ~output_settings() = default;

public:
    output_settings();

public:
    output_settings(
        const bool output_to_stdout,
        const bool output_to_file,
        const bool delete_extra_files,
        const bool force_write,
        const std::vector<std::string>& ignore_patterns);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const output_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, output_settings& v, unsigned int version);

public:
    /**
     * @brief Output generated code to standard output.
     */
    /**@{*/
    bool output_to_stdout() const;
    void output_to_stdout(const bool v);
    /**@}*/

    /**
     * @brief Output generated code to files.
     */
    /**@{*/
    bool output_to_file() const;
    void output_to_file(const bool v);
    /**@}*/

    /**
     * @brief Delete any extra files found in managed directories.
     */
    /**@{*/
    bool delete_extra_files() const;
    void delete_extra_files(const bool v);
    /**@}*/

    /**
     * @brief Always generate files even if there are no differences
     * with existing file.
     */
    /**@{*/
    bool force_write() const;
    void force_write(const bool v);
    /**@}*/

    /**
     * @brief List of regular expressions to filter out files to ignore.
     */
    /**@{*/
    const std::vector<std::string>& ignore_patterns() const;
    std::vector<std::string>& ignore_patterns();
    void ignore_patterns(const std::vector<std::string>& v);
    void ignore_patterns(const std::vector<std::string>&& v);
    /**@}*/

public:
    bool operator==(const output_settings& rhs) const;
    bool operator!=(const output_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(output_settings& other) noexcept;
    output_settings& operator=(output_settings other);

private:
    bool output_to_stdout_;
    bool output_to_file_;
    bool delete_extra_files_;
    bool force_write_;
    std::vector<std::string> ignore_patterns_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::config::output_settings& lhs,
    dogen::config::output_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
