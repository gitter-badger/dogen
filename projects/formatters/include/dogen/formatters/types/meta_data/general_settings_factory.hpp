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
#ifndef DOGEN_FORMATTERS_TYPES_META_DATA_GENERAL_SETTINGS_FACTORY_HPP
#define DOGEN_FORMATTERS_TYPES_META_DATA_GENERAL_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/formatters/types/modeline_group.hpp"
#include "dogen/formatters/types/licence.hpp"

namespace dogen {
namespace formatters {
namespace meta_data {

/**
 * @brief Creates the general settings by extracting information from
 * meta-data.
 */
class general_settings_factory {
public:
    general_settings_factory() = delete;
    general_settings_factory(const general_settings_factory&) = default;
    general_settings_factory(general_settings_factory&&) = default;
    ~general_settings_factory() = default;

public:
    /**
     * @brief Initialise a new general settings factory.
     *
     * @param data_files_directories where to look for reference data.
     */
    explicit general_settings_factory(
        const std::forward_list<boost::filesystem::path>& data_files_dirs);

private:
    /*
     * @brief Throws an exception due to a missing item.
     */
    void throw_missing_item(const std::string& msg, const std::string& n) const;

    /**
     * @brief Extracts a licence using meta-data in the Taggable.
     */
    boost::optional<licence> extract_licence(
        const boost::property_tree::ptree& md) const;

    /**
     * @brief Extracts a modeline using meta-data in the Taggable.
     */
    boost::optional<modeline> extract_modeline(
        const boost::property_tree::ptree& meta_data) const;

    /**
     * @brief Extracts a code generation marker using meta-data in the
     * Taggable.
     */
    std::string extract_marker(
        const boost::property_tree::ptree& meta_data) const;

private:
    /**
     * @brief Creates the actual list of directories used by hydrators
     * to load data.
     */
    std::forward_list<boost::filesystem::path>
    create_directory_list(const std::string& for_whom) const;

    /**
     * @brief Hydrates all the modelines available in the library.
     */
    void hydrate_modelines();

    /**
     * @brief Hydrates all the licences available in the library.
     */
    void hydrate_licences();

    /**
     * @brief Creates the code generation marker.
     */
    void create_marker(const boost::property_tree::ptree& meta_data);

public:
    /**
     * @brief Returns true if there is any reference data at all in the
     * factory.
     *
     * @note This method is mainly for tests.
     */
    bool empty() const;

    /**
     * @brief Loads all of the required reference data from the file
     * system.
     */
    void load_reference_data();

    /**
     * @brief Generates general settings from the meta-data.
     *
     * @pre load reference data must have been called.
     */
    general_settings build(const boost::property_tree::ptree& meta_data) const;

private:
    const std::forward_list<boost::filesystem::path>& data_files_directories_;
    std::unordered_map<std::string, modeline_group> modeline_groups_;
    std::unordered_map<std::string, licence> licences_;
};

} } }

#endif
