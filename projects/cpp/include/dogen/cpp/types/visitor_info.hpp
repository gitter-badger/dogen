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
#ifndef DOGEN_CPP_TYPES_VISITOR_INFO_HPP
#define DOGEN_CPP_TYPES_VISITOR_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include <string>
#include "dogen/cpp/serialization/visitor_info_fwd_ser.hpp"
#include "dogen/cpp/types/entity.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Represents a C++ class modeling the visitor pattern.
 */
class visitor_info final : public dogen::cpp::entity {
public:
    visitor_info() = default;
    visitor_info(const visitor_info&) = default;
    visitor_info(visitor_info&&) = default;

    virtual ~visitor_info() noexcept { }

public:
    visitor_info(
        const std::string& name,
        const std::string& documentation,
        const std::list<std::string>& namespaces,
        const std::unordered_map<std::string, boost::filesystem::path>& relative_path_for_formatter,
        const std::unordered_map<std::string, dogen::cpp::includes>& includes_for_formatter,
        const std::list<std::string>& types);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const visitor_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, visitor_info& v, unsigned int version);

public:
    virtual void accept(const entity_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(entity_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const entity_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(entity_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Types for which an accept method will be generated.
     */
    /**@{*/
    const std::list<std::string>& types() const;
    std::list<std::string>& types();
    void types(const std::list<std::string>& v);
    void types(const std::list<std::string>&& v);
    /**@}*/

public:
    bool operator==(const visitor_info& rhs) const;
    bool operator!=(const visitor_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cpp::entity& other) const override;

public:
    void swap(visitor_info& other) noexcept;
    visitor_info& operator=(visitor_info other);

private:
    std::list<std::string> types_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::visitor_info& lhs,
    dogen::cpp::visitor_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
