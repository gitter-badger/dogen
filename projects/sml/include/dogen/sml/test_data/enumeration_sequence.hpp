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
#ifndef DOGEN_SML_TEST_DATA_ENUMERATION_SEQUENCE_HPP
#define DOGEN_SML_TEST_DATA_ENUMERATION_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"
#include "dogen/sml/domain/enumeration.hpp"
#include "dogen/sml/test_data/property_sequence.hpp"
#include "dogen/sml/test_data/qualified_name_sequence.hpp"
#include "dogen/sml/test_data/enumerator_sequence.hpp"

namespace dogen {
namespace sml {
namespace test_data {

namespace detail {

/**
 * @brief Generates an open ended sequence of versions.
 *
 * @see sequence.
 */
class enumeration_generator {
public:
    typedef dogen::sml::enumeration result_type;

public:
    result_type next_term(const unsigned int position) {
        dogen::sml::enumeration result;
        dogen::sml::test_data::qualified_name_sequence sequence;
        dogen::sml::test_data::enumerator_sequence seq2;

        result.generate(true);
        std::vector<sml::enumerator> enumerators;
        if (position == 1) {
            result.name(sequence());
            result.documentation("enum docs 1");
            enumerators.push_back(seq2());
        } else if (position == 2) {
            sequence();
            result.name(sequence());
            result.documentation("enum docs 2");
            enumerators.push_back(seq2());
            enumerators.push_back(seq2());
        } else {
            sequence();
            sequence();
            result.name(sequence());
            result.documentation("enum docs 3");
            enumerators.push_back(seq2());
            enumerators.push_back(seq2());
            enumerators.push_back(seq2());
        }
        result.enumerators(enumerators);
        return result;
    }

    unsigned int length() const { return(3); }
};

}

typedef utility::test_data::sequence<
    detail::enumeration_generator> enumeration_sequence;

} } }


#endif