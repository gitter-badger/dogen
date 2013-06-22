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
#ifndef DOGEN_SML_SERIALIZATION_CONCEPT_SER_HPP
#define DOGEN_SML_SERIALIZATION_CONCEPT_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/split_free.hpp>
#include <boost/type_traits/is_virtual_base_of.hpp>
#include "dogen/sml/types/concept.hpp"

namespace boost {

template<>struct
is_virtual_base_of<
    dogen::sml::model_element,
    dogen::sml::concept
> : public mpl::true_ {};

}

BOOST_SERIALIZATION_SPLIT_FREE(dogen::sml::concept)
namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar, const dogen::sml::concept& v, unsigned int version);

template<typename Archive>
void load(Archive& ar, dogen::sml::concept& v, unsigned int version);

} }

#endif