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
#include "dogen/test_models/std_model/hash/class_a_hash.hpp"
#include "dogen/test_models/std_model/hash/class_e_hash.hpp"
#include "dogen/test_models/std_model/hash/pkg1/class_c_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_deque_std_string(const std::deque<std::string>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_deque_dogen_test_models_std_model_class_a(const std::deque<dogen::test_models::std_model::class_a>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_deque_dogen_test_models_std_model_pkg1_class_c(const std::deque<dogen::test_models::std_model::pkg1::class_c>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_deque_unsigned_int(const std::deque<unsigned int>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_deque_std_deque_unsigned_int_(const std::deque<std::deque<unsigned int> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_deque_unsigned_int(i));
    }
    return seed;
}

}

namespace dogen {
namespace test_models {
namespace std_model {

std::size_t class_e_hasher::hash(const class_e&v) {
    std::size_t seed(0);

    combine(seed, hash_std_deque_std_string(v.prop_0()));
    combine(seed, hash_std_deque_dogen_test_models_std_model_class_a(v.prop_1()));
    combine(seed, hash_std_deque_dogen_test_models_std_model_pkg1_class_c(v.prop_2()));
    combine(seed, hash_std_deque_unsigned_int(v.prop_3()));
    combine(seed, hash_std_deque_dogen_test_models_std_model_class_a(v.prop_4()));
    combine(seed, hash_std_deque_std_deque_unsigned_int_(v.prop_5()));

    return seed;
}

} } }
