// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_EOLF_HPP
#define TAO_PEGTL_INTERNAL_EOLF_HPP

#include "enable_control.hpp"

#include "../type_list.hpp"

namespace tao::pegtl::internal
{
   struct eolf
   {
      using rule_t = eolf;
      using subs_t = empty_list;

      template< apply_mode A,
                rewind_mode M,
                template< typename... >
                class Action,
                template< typename... >
                class Control,
                typename ParseInput,
                typename... States >
      [[nodiscard]] static bool match( ParseInput& in, States&&... st )
      {
         return in.empty() || in.template match_eol< A, M, Action, Control >( in, st... );
      }
   };

   template<>
   inline constexpr bool enable_control< eolf > = false;

}  // namespace tao::pegtl::internal

#endif
