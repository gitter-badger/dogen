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
#include <ostream>
#include "dogen/cpp/io/entity_io.hpp"
#include "dogen/cpp/io/state_io.hpp"
#include "dogen/cpp/types/concept_info.hpp"

namespace dogen {
namespace cpp {

concept_info::concept_info(
    const std::string& name,
    const std::string& documentation,
    const std::list<std::string>& namespaces,
    const std::unordered_map<std::string, dogen::cpp::file_settings>& file_settings_for_formatter,
    const dogen::cpp::state& state)
    : dogen::cpp::entity(name,
      documentation,
      namespaces,
      file_settings_for_formatter),
      state_(state) { }

void concept_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::concept_info\"" << ", "
      << "\"__parent_0__\": ";
    entity::to_stream(s);
    s << ", "
      << "\"state\": " << state_
      << " }";
}

void concept_info::swap(concept_info& other) noexcept {
    entity::swap(other);

    using std::swap;
    swap(state_, other.state_);
}

bool concept_info::equals(const dogen::cpp::entity& other) const {
    const concept_info* const p(dynamic_cast<const concept_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool concept_info::operator==(const concept_info& rhs) const {
    return entity::compare(rhs) &&
        state_ == rhs.state_;
}

concept_info& concept_info::operator=(concept_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::cpp::state& concept_info::state() const {
    return state_;
}

dogen::cpp::state& concept_info::state() {
    return state_;
}

void concept_info::state(const dogen::cpp::state& v) {
    state_ = v;
}

void concept_info::state(const dogen::cpp::state&& v) {
    state_ = std::move(v);
}

} }