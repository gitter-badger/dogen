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
#ifndef DOGEN_SML_TYPES_SERVICE_HPP
#define DOGEN_SML_TYPES_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include <list>
#include <string>
#include <utility>
#include <vector>
#include "dogen/sml/serialization/service_fwd_ser.hpp"
#include "dogen/sml/types/generation_types.hpp"
#include "dogen/sml/types/property.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/service_types.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a class with behaviour.
 *
 * We have distorted the use of services as defined by DDD because its not
 * possible to attach non-trivial behaviour to pods. Thus anything which requires
 * non-trivial behaviour has to be a service in Dogen.
 */
class service final {
public:
    service(const service&) = default;
    ~service() = default;

public:
    service();

public:
    service(service&& rhs);

public:
    service(
        const dogen::sml::qname& name,
        const std::vector<dogen::sml::property>& properties,
        const boost::optional<dogen::sml::qname>& parent_name,
        const boost::optional<dogen::sml::qname>& original_parent_name,
        const std::list<dogen::sml::qname>& leaves,
        const dogen::sml::generation_types& generation_type,
        const bool is_parent,
        const dogen::sml::service_types& service_type,
        const std::string& documentation,
        const unsigned int number_of_type_arguments,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
        const bool is_visitable);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const service& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, service& v, unsigned int version);

public:
    /**
     * @brief Qualified name for the type.
     *
     */
    /**@{*/
    const dogen::sml::qname& name() const;
    dogen::sml::qname& name();
    void name(const dogen::sml::qname& v);
    void name(const dogen::sml::qname&& v);
    /**@}*/

    /**
     * @brief All the properties this pod owns.
     */
    /**@{*/
    const std::vector<dogen::sml::property>& properties() const;
    std::vector<dogen::sml::property>& properties();
    void properties(const std::vector<dogen::sml::property>& v);
    void properties(const std::vector<dogen::sml::property>&& v);
    /**@}*/

    /**
     * @brief Qualified name for the pod's parent, if the pod has one.
     */
    /**@{*/
    const boost::optional<dogen::sml::qname>& parent_name() const;
    boost::optional<dogen::sml::qname>& parent_name();
    void parent_name(const boost::optional<dogen::sml::qname>& v);
    void parent_name(const boost::optional<dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief Qualified name for the root of the inheritance hierarchy, if the pod is part of one.
     */
    /**@{*/
    const boost::optional<dogen::sml::qname>& original_parent_name() const;
    boost::optional<dogen::sml::qname>& original_parent_name();
    void original_parent_name(const boost::optional<dogen::sml::qname>& v);
    void original_parent_name(const boost::optional<dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief All concrete types which are indirectly or directly derived from this type.
     */
    /**@{*/
    const std::list<dogen::sml::qname>& leaves() const;
    std::list<dogen::sml::qname>& leaves();
    void leaves(const std::list<dogen::sml::qname>& v);
    void leaves(const std::list<dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief What to do with this pod in terms of code generation
     */
    /**@{*/
    dogen::sml::generation_types generation_type() const;
    void generation_type(const dogen::sml::generation_types& v);
    /**@}*/

    /**
     * @brief True if this class is the parent of one or more classes, false otherwise.
     */
    /**@{*/
    bool is_parent() const;
    void is_parent(const bool v);
    /**@}*/

    /**
     * @brief Type of this service.
     */
    /**@{*/
    dogen::sml::service_types service_type() const;
    void service_type(const dogen::sml::service_types& v);
    /**@}*/

    /**
     * @brief Doxygen documentation for the type.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief How many type arguments does this type have
     */
    /**@{*/
    unsigned int number_of_type_arguments() const;
    void number_of_type_arguments(const unsigned int v);
    /**@}*/

    /**
     * @brief Parameters associated with the pod which are opaque to SML.
     */
    /**@{*/
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters() const;
    std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters();
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v);
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v);
    /**@}*/

    /**
     * @brief If true, a visitor is to be generated for this type and its descendants.
     *
     * Only applicable if is_parent is true.
     */
    /**@{*/
    bool is_visitable() const;
    void is_visitable(const bool v);
    /**@}*/

public:
    bool operator==(const service& rhs) const;
    bool operator!=(const service& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(service& other) noexcept;
    service& operator=(service other);

private:
    dogen::sml::qname name_;
    std::vector<dogen::sml::property> properties_;
    boost::optional<dogen::sml::qname> parent_name_;
    boost::optional<dogen::sml::qname> original_parent_name_;
    std::list<dogen::sml::qname> leaves_;
    dogen::sml::generation_types generation_type_;
    bool is_parent_;
    dogen::sml::service_types service_type_;
    std::string documentation_;
    unsigned int number_of_type_arguments_;
    std::vector<std::pair<std::string, std::string> > implementation_specific_parameters_;
    bool is_visitable_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::service& lhs,
    dogen::sml::service& rhs) {
    lhs.swap(rhs);
}

}

#endif