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
#include "dogen/config/types/input_settings.hpp"

namespace dogen {
namespace config {

input_settings::input_settings()
    : disable_model_module_(static_cast<bool>(0)) { }

input_settings::input_settings(input_settings&& rhs)
    : target_(std::move(rhs.target_)),
      external_module_path_(std::move(rhs.external_module_path_)),
      references_(std::move(rhs.references_)),
      disable_model_module_(std::move(rhs.disable_model_module_)) { }

input_settings::input_settings(
    const boost::filesystem::path& target,
    const std::string& external_module_path,
    const std::vector<dogen::config::reference>& references,
    const bool disable_model_module)
    : target_(target),
      external_module_path_(external_module_path),
      references_(references),
      disable_model_module_(disable_model_module) { }

void input_settings::swap(input_settings& other) noexcept {
    using std::swap;
    swap(target_, other.target_);
    swap(external_module_path_, other.external_module_path_);
    swap(references_, other.references_);
    swap(disable_model_module_, other.disable_model_module_);
}

bool input_settings::operator==(const input_settings& rhs) const {
    return target_ == rhs.target_ &&
        external_module_path_ == rhs.external_module_path_ &&
        references_ == rhs.references_ &&
        disable_model_module_ == rhs.disable_model_module_;
}

input_settings& input_settings::operator=(input_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& input_settings::target() const {
    return target_;
}

boost::filesystem::path& input_settings::target() {
    return target_;
}

void input_settings::target(const boost::filesystem::path& v) {
    target_ = v;
}

void input_settings::target(const boost::filesystem::path&& v) {
    target_ = std::move(v);
}

const std::string& input_settings::external_module_path() const {
    return external_module_path_;
}

std::string& input_settings::external_module_path() {
    return external_module_path_;
}

void input_settings::external_module_path(const std::string& v) {
    external_module_path_ = v;
}

void input_settings::external_module_path(const std::string&& v) {
    external_module_path_ = std::move(v);
}

const std::vector<dogen::config::reference>& input_settings::references() const {
    return references_;
}

std::vector<dogen::config::reference>& input_settings::references() {
    return references_;
}

void input_settings::references(const std::vector<dogen::config::reference>& v) {
    references_ = v;
}

void input_settings::references(const std::vector<dogen::config::reference>&& v) {
    references_ = std::move(v);
}

bool input_settings::disable_model_module() const {
    return disable_model_module_;
}

void input_settings::disable_model_module(const bool v) {
    disable_model_module_ = v;
}

} }