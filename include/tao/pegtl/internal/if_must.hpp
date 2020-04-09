// Copyright (c) 2014-2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_INTERNAL_IF_MUST_HPP
#define TAO_PEGTL_INTERNAL_IF_MUST_HPP

#include "../config.hpp"

#include "enable_control.hpp"
#include "must.hpp"

#include "../apply_mode.hpp"
#include "../rewind_mode.hpp"
#include "../rule_list.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   template< bool Default, typename Cond, typename... Rules >
   struct if_must
   {
      using rule_t = if_must;
      using subs_t = rule_list< Cond, must< Rules... > >;

      template< apply_mode A,
                rewind_mode M,
                template< typename... >
                class Action,
                template< typename... >
                class Control,
                typename Input,
                typename... States >
      [[nodiscard]] static bool match( Input& in, States&&... st )
      {
         if( Control< Cond >::template match< A, M, Action, Control >( in, st... ) ) {
            (void)Control< must< Rules... > >::template match< A, M, Action, Control >( in, st... );
            return true;
         }
         return Default;
      }
   };

   template< bool Default, typename Cond, typename... Rules >
   inline constexpr bool enable_control< if_must< Default, Cond, Rules... > > = false;

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif
