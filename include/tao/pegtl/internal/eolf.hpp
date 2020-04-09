// Copyright (c) 2014-2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_INTERNAL_EOLF_HPP
#define TAO_PEGTL_INTERNAL_EOLF_HPP

#include "../config.hpp"

#include "enable_control.hpp"

#include "../rule_list.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   struct eolf
   {
      using rule_t = eolf;
      using subs_t = empty_list;

      template< typename Input >
      [[nodiscard]] static bool match( Input& in ) noexcept( noexcept( Input::eol_t::match( in ) ) )
      {
         const auto p = Input::eol_t::match( in );
         return p.first || ( !p.second );
      }
   };

   template<>
   inline constexpr bool enable_control< eolf > = false;

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif
