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
#ifndef DOGEN_DIA_TO_SML_TYPES_PROCESSOR_HPP
#define DOGEN_DIA_TO_SML_TYPES_PROCESSOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dia/types/attribute_fwd.hpp"
#include "dogen/dia/types/object_fwd.hpp"
#include "dogen/dia/types/attribute_fwd.hpp"
#include "dogen/dia/types/composite_fwd.hpp"
#include "dogen/dia_to_sml/types/object_types.hpp"
#include "dogen/dia_to_sml/types/processed_object_fwd.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Processes dia objects into an intermediate format.
 */
class processor {
public:
    processor() = default;
    processor(const processor&) = delete;
    processor(processor&&) = default;

private:
    /**
     * @brief Parses the dia attribute as a string, returning its value.
     */
    std::string parse_string_attribute(const dia::attribute& a) const;

    /**
     * @brief Given a string with a dia object type, returns the
     * appropriate enum.
     */
    object_types parse_object_type(const std::string& ot) const;

public:
    /**
     * @brief Process the object.
     */
    processed_object process(const dia::object& o);
};

} }

#endif
