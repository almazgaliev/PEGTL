// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_HAS_CURRENT_POSITION_HPP
#define TAO_PEGTL_INTERNAL_HAS_CURRENT_POSITION_HPP

#include <utility>

namespace tao::pegtl::internal
{
   template< typename, typename = void >
   inline constexpr bool has_current_position = false;

   template< typename C >
   inline constexpr bool has_current_position< C, decltype( std::declval< C >().current_position() ) > = true;

}  // namespace tao::pegtl::internal

#endif
