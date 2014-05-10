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
#ifndef DOGEN_KNIT_TYPES_WORKFLOW_HPP
#define DOGEN_KNIT_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <utility>
#include <functional>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/model.hpp"
#include "dogen/config/types/knitting_settings.hpp"
#include "dogen/config/types/formatting_settings.hpp"
#include "dogen/knit/types/backends/backend.hpp"
#include "dogen/knit/types/outputters/outputter.hpp"
#include "dogen/utility/serialization/archive_types.hpp"

namespace dogen {
namespace knit {

/**
 * @brief Main workflow of the Knit library. Responsible for
 * transforming a high-level representation of a domain into code, in
 * one or more programming languages.
 *
 * The model which one intends to transform is known as the @e target
 * model. The workflow starts by invoking the correct front-end to
 * read in the target model and all of its dependencies. There are two
 * types of dependencies:
 *
 * @li @e explicit: specified by the settings passed in; these are
 * models created by the user and any models that they, in turn,
 * depend on.
 *
 * @li @e implicit: these are known as the @e system models. They are
 * added automatically. Examples are primitives, boost, std, etc.
 *
 * Collectively, all implicit and explicit models are referred to as
 * the @e input models. The input models read the front-end are
 * converted into the middle end representation - SML. They are then
 * merged it into a single, unified SML model, called the @e merged
 * model; all dependencies are resolved and validated.
 *
 * The workflow then instantiates all backends requested by the
 * settings passed in. They use the merged model to generate source
 * code, and then outputted it to the desired destination.
 */
class workflow {
public:
    workflow() = delete;
    workflow& operator=(const workflow&) = default;
    workflow(const workflow&) = default;

public:
    typedef std::function<std::ostream& ()> output_fn;

public:
    workflow(workflow&& rhs);
    workflow(const config::knitting_settings& s);
    workflow(const config::knitting_settings& s, const output_fn& o);

public: // public section for testing purposes only
    /**
     * @brief Returns true if the housekeeping of generated files is
     * required, false otherwise.
     */
    bool housekeeping_required() const;

private:
    /**
     * @brief Performs a housekeeping run for the supplied directories.
     */
    void housekeep(const std::map<boost::filesystem::path, std::string>& files,
        const std::vector<boost::filesystem::path>& dirs) const;

    /**
     * @brief Outputs the pair file name and contents to its output
     * destination.
     */
    void output_files(const outputters::outputter::value_type& o) const;

    /**
     * @brief Transforms the model into generated code, according to
     * the backend passed in.
     */
    void create_files_for_backend(backends::backend& b) const;

    /**
     * @brief Returns true if we should execute the generation
     * activity, false otherwise.
     */
    bool is_generation_required(const boost::optional<sml::model>& m) const;

public:
    /**
     * @brief Execute the SML workflow and return a model that can be
     * generated - or nothing, if no such model exists.
     */
    boost::optional<sml::model> obtain_model_activity() const;

    /**
     * @brief Extracts the formatting settings from the SML model.
     */
    config::formatting_settings
    extract_formatting_settings_activity(const sml::model& m) const;

    /**
     * @brief Given a merged model, generates all of its
     * representations.
     */
    void generate_model_activity(const sml::model& m,
        const config::formatting_settings& fs) const;

public:
    /**
     * @brief Perform the entire code generation workflow.
     */
    void execute() const;

private:
    const config::knitting_settings knitting_settings_;
    const output_fn output_;
};

} }

#endif