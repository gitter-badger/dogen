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
#ifndef DOGEN_OM_TYPES_ANNOTATION_HPP
#define DOGEN_OM_TYPES_ANNOTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/om/serialization/annotation_fwd_ser.hpp"
#include "dogen/om/types/licence.hpp"
#include "dogen/om/types/modeline.hpp"

namespace dogen {
namespace om {

/**
 * @brief Aggregates all the file meta-data in one place.
 */
class annotation final {
public:
    annotation() = default;
    annotation(const annotation&) = default;
    annotation(annotation&&) = default;
    ~annotation() = default;

public:
    annotation(
        const dogen::om::modeline& modeline,
        const dogen::om::licence& licence,
        const std::string& code_generation_marker);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const annotation& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, annotation& v, unsigned int version);

public:
    /**
     * @brief Modeline to use in this file.
     */
    /**@{*/
    const dogen::om::modeline& modeline() const;
    dogen::om::modeline& modeline();
    void modeline(const dogen::om::modeline& v);
    void modeline(const dogen::om::modeline&& v);
    /**@}*/

    /**
     * @brief Licence to use in this file.
     */
    /**@{*/
    const dogen::om::licence& licence() const;
    dogen::om::licence& licence();
    void licence(const dogen::om::licence& v);
    void licence(const dogen::om::licence&& v);
    /**@}*/

    /**
     * @brief Code generation marker to use in this file.
     */
    /**@{*/
    const std::string& code_generation_marker() const;
    std::string& code_generation_marker();
    void code_generation_marker(const std::string& v);
    void code_generation_marker(const std::string&& v);
    /**@}*/

public:
    bool operator==(const annotation& rhs) const;
    bool operator!=(const annotation& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(annotation& other) noexcept;
    annotation& operator=(annotation other);

private:
    dogen::om::modeline modeline_;
    dogen::om::licence licence_;
    std::string code_generation_marker_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::annotation& lhs,
    dogen::om::annotation& rhs) {
    lhs.swap(rhs);
}

}

#endif