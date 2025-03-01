// Copyright (c) 2023 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_STAR_STRICT_HPP
#define TAO_PEGTL_INTERNAL_STAR_STRICT_HPP

#include "enable_control.hpp"
#include "seq.hpp"

#include "../apply_mode.hpp"
#include "../rewind_mode.hpp"
#include "../type_list.hpp"

namespace tao::pegtl::internal
{
   template< typename Rule, typename... Rules >
   struct star_strict
   {
      using rule_t = star_strict;
      using subs_t = type_list< Rule, Rules... >;

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
         auto m = in.template auto_rewind< M >();
         using m_t = decltype( m );

         while( Control< Rule >::template match< A, rewind_mode::required, Action, Control >( in, st... ) ) {
            if( Control< seq< Rules... > >::template match< A, m_t::next_rewind_mode, Action, Control >( in, st... ) ) {
               continue;
            }
            return m( false );
         }
         return m( true );
      }
   };

   template< typename... Rules >
   inline constexpr bool enable_control< star_strict< Rules... > > = false;

}  // namespace tao::pegtl::internal

#endif
