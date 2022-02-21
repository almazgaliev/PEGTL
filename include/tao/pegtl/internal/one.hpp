// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_ONE_HPP
#define TAO_PEGTL_INTERNAL_ONE_HPP

#include <cstddef>

#include "enable_control.hpp"
#include "failure.hpp"
#include "many.hpp"
#include "result_on_found.hpp"

#include "../type_list.hpp"

namespace tao::pegtl::internal
{
   template< result_on_found R, typename Peek, typename Peek::data_t... Cs >
   struct one
   {
      using peek_t = Peek;
      using data_t = typename Peek::data_t;

      using rule_t = one;
      using subs_t = empty_list;

      [[nodiscard]] static constexpr bool test_one( const data_t c ) noexcept
      {
         return ( ( c == Cs ) || ... ) == bool( R );
      }

      template< typename ParseInput >
      [[nodiscard]] static bool match( ParseInput& in ) noexcept( noexcept( Peek::peek( in ) ) )
      {
         if( const auto t = Peek::peek( in ) ) {
            if( test_one( t.data() ) ) {
               in.template consume< one >( t.size() );
               return true;
            }
         }
         return false;
      }
   };

   template< typename Peek >
   struct one< result_on_found::success, Peek >
      : failure
   {};

   template< typename Peek >
   struct one< result_on_found::failure, Peek >
      : any< Peek >
   {};

   template< result_on_found R, typename Peek, typename Peek::data_t... Cs >
   inline constexpr bool enable_control< one< R, Peek, Cs... > > = false;

}  // namespace tao::pegtl::internal

#endif
