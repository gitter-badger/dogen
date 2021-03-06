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
#include "dogen/utility/log/logger.hpp"
#include "dogen/knit/types/backends/cpp_backend.hpp"
#include "dogen/knit/types/backends/factory.hpp"

static dogen::utility::log::logger
lg(dogen::utility::log::logger_factory("knit.backends.factory"));

namespace dogen {
namespace knit {
namespace backends {

factory::factory(const sml::model& model, const config::formatting_settings& s)
    : settings_(s), model_(model) { }

void factory::log_cpp_backend_disabled() const {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, info) << "C++ backend is disabled, skipping it.";
}

factory::result_type factory::create() const {
    if (settings_.cpp().disable_backend()) {
        log_cpp_backend_disabled();
        return result_type();
    }

    result_type r;
    r.push_back(cpp_backend::create(model_, settings_));
    return r;
}

} } }
