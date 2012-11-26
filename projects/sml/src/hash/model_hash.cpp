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
#include "dogen/sml/hash/enumeration_hash.hpp"
#include "dogen/sml/hash/exception_hash.hpp"
#include "dogen/sml/hash/model_hash.hpp"
#include "dogen/sml/hash/package_hash.hpp"
#include "dogen/sml/hash/pod_hash.hpp"
#include "dogen/sml/hash/primitive_hash.hpp"
#include "dogen/sml/hash/qualified_name_hash.hpp"
#include "dogen/sml/hash/reference_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_dogen_sml_qualified_name_dogen_sml_package(const std::unordered_map<dogen::sml::qualified_name, dogen::sml::package>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qualified_name_dogen_sml_pod(const std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qualified_name_dogen_sml_primitive(const std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qualified_name_dogen_sml_enumeration(const std::unordered_map<dogen::sml::qualified_name, dogen::sml::enumeration>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qualified_name_dogen_sml_exception(const std::unordered_map<dogen::sml::qualified_name, dogen::sml::exception>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_list_std_string(const std::list<std::string>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_sml_reference(const std::unordered_map<std::string, dogen::sml::reference>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_set_dogen_sml_qualified_name(const std::unordered_set<dogen::sml::qualified_name>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace sml {

std::size_t model_hasher::hash(const model&v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, hash_std_unordered_map_dogen_sml_qualified_name_dogen_sml_package(v.packages()));
    combine(seed, hash_std_unordered_map_dogen_sml_qualified_name_dogen_sml_pod(v.pods()));
    combine(seed, hash_std_unordered_map_dogen_sml_qualified_name_dogen_sml_primitive(v.primitives()));
    combine(seed, hash_std_unordered_map_dogen_sml_qualified_name_dogen_sml_enumeration(v.enumerations()));
    combine(seed, hash_std_unordered_map_dogen_sml_qualified_name_dogen_sml_exception(v.exceptions()));
    combine(seed, hash_std_list_std_string(v.external_package_path()));
    combine(seed, v.schema_name());
    combine(seed, v.is_system());
    combine(seed, hash_std_unordered_map_std_string_dogen_sml_reference(v.dependencies()));
    combine(seed, hash_std_unordered_set_dogen_sml_qualified_name(v.leaves()));

    return seed;
}

} }