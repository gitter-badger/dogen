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
#include "dogen/cpp/serialization/abilities_ser.hpp"
#include "dogen/cpp/serialization/aspect_types_ser.hpp"
#include "dogen/cpp/serialization/class_aspects_ser.hpp"
#include "dogen/cpp/serialization/class_info_ser.hpp"
#include "dogen/cpp/serialization/class_types_ser.hpp"
#include "dogen/cpp/serialization/cmakelists_info_ser.hpp"
#include "dogen/cpp/serialization/concept_info_ser.hpp"
#include "dogen/cpp/serialization/content_descriptor_ser.hpp"
#include "dogen/cpp/serialization/content_types_ser.hpp"
#include "dogen/cpp/serialization/cpp_settings_ser.hpp"
#include "dogen/cpp/serialization/entity_ser.hpp"
#include "dogen/cpp/serialization/enum_info_ser.hpp"
#include "dogen/cpp/serialization/enumerator_info_ser.hpp"
#include "dogen/cpp/serialization/exception_info_ser.hpp"
#include "dogen/cpp/serialization/facet_settings_ser.hpp"
#include "dogen/cpp/serialization/file_info_ser.hpp"
#include "dogen/cpp/serialization/file_settings_ser.hpp"
#include "dogen/cpp/serialization/file_types_ser.hpp"
#include "dogen/cpp/serialization/formatter_settings_ser.hpp"
#include "dogen/cpp/serialization/formatters/formatter_types_ser.hpp"
#include "dogen/cpp/serialization/formatters/odb/settings_ser.hpp"
#include "dogen/cpp/serialization/formatters/serialization/settings_ser.hpp"
#include "dogen/cpp/serialization/global_settings_ser.hpp"
#include "dogen/cpp/serialization/includes_ser.hpp"
#include "dogen/cpp/serialization/inheritance_ser.hpp"
#include "dogen/cpp/serialization/namespace_info_ser.hpp"
#include "dogen/cpp/serialization/nested_type_info_ser.hpp"
#include "dogen/cpp/serialization/new_class_info_ser.hpp"
#include "dogen/cpp/serialization/odb_options_info_ser.hpp"
#include "dogen/cpp/serialization/parent_info_ser.hpp"
#include "dogen/cpp/serialization/primitive_info_ser.hpp"
#include "dogen/cpp/serialization/project_ser.hpp"
#include "dogen/cpp/serialization/property_info_ser.hpp"
#include "dogen/cpp/serialization/registrar_info_ser.hpp"
#include "dogen/cpp/serialization/registrar_ser.hpp"
#include "dogen/cpp/serialization/state_ser.hpp"
#include "dogen/cpp/serialization/visitor_info_ser.hpp"
