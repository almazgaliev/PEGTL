// Copyright (c) 2014-2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_INTERNAL_RANGE_HPP
#define TAO_PEGTL_INTERNAL_RANGE_HPP

#include "../config.hpp"

#include "enable_control.hpp"
#include "result_on_found.hpp"

#include "../rule_list.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   template< result_on_found R, typename Peek, typename Peek::data_t Lo, typename Peek::data_t Hi >
   struct range
   {
      using rule_t = range;
      using subs_t = empty_list;

      static_assert( Lo <= Hi, "invalid range detected" );

      template< int Eol >
      static constexpr bool can_match_eol = ( ( ( Lo <= Eol ) && ( Eol <= Hi ) ) == bool( R ) );

      template< typename Input >
      [[nodiscard]] static bool match( Input& in ) noexcept( noexcept( in.size( Peek::max_input_size ) ) )
      {
         if( const std::size_t s = in.size( Peek::max_input_size ); s >= Peek::min_input_size ) {
            if( const auto t = Peek::peek( in, s ) ) {
               if( ( ( Lo <= t.data ) && ( t.data <= Hi ) ) == bool( R ) ) {
                  if constexpr( can_match_eol< Input::eol_t::ch > ) {
                     in.bump( t.size );
                  }
                  else {
                     in.bump_in_this_line( t.size );
                  }
                  return true;
               }
            }
         }
         return false;
      }
   };

   template< result_on_found R, typename Peek, typename Peek::data_t Lo, typename Peek::data_t Hi >
   inline constexpr bool enable_control< range< R, Peek, Lo, Hi > > = false;

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif
