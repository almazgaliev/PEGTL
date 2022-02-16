// Copyright (c) 2017-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_ENDIAN_WIN_HPP
#define TAO_PEGTL_INTERNAL_ENDIAN_WIN_HPP

#include <cstdint>
#include <type_traits>

#include "dependent_false.hpp"

namespace tao::pegtl::internal
{
#define TAO_PEGTL_ENDIAN_SUFFIXED( iDeNTiFieR ) iDeNTiFieR ## le

   template< typename T >
   T little_endian::from( const T n ) noexcept
   {
      static_assert( std::is_integral_v< T > || std::is_enum_v< T > );
      return n;
   }

   template< typename T >
   T big_endian::from( const T n ) noexcept
   {
      static_assert( std::is_integral_v< T > || std::is_enum_v< T > );

      if constexpr( sizeof( T ) == 1 ) {
         return n;
      }
      else if constexpr( sizeof( T ) == 2 ) {
         return static_cast< T >( _byteswap_ushort( static_cast< std::uint16_t >( n ) ) );
      }
      else if constexpr( sizeof( T ) == 4 ) {
         return static_cast< T >( _byteswap_ulong( static_cast< std::uint32_t >( n ) ) );
      }
      else if constexpr( sizeof( T ) == 8 ) {
         return static_cast< T >( _byteswap_uint64( static_cast< std::uint64_t >( n ) ) );
      }
      else {
         static_assert( dependent_false< T > );
      }
   }

   using other_endian = big_endian;
   using native_endian = little_endian;

}  // namespace tao::pegtl::internal

#endif
