// Copyright (c) 2017-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_INTERNAL_ENDIAN_HPP
#define TAO_PEGTL_CONTRIB_INTERNAL_ENDIAN_HPP

#include <cstring>

namespace tao::pegtl::internal
{
   struct big_endian
   {
      template< typename T >
      [[nodiscard]] static T from( const T n ) noexcept;

      template< typename T >
      [[nodiscard]] static T from( const void* p ) noexcept
      {
         T n;
         std::memcpy( &n, p, sizeof( n ) );
         return from( n );
      }
   };

   struct little_endian
   {
      template< typename T >
      [[nodiscard]] static T from( const T n ) noexcept;

      template< typename T >
      [[nodiscard]] static T from( const void* p ) noexcept
      {
         T n;
         std::memcpy( &n, p, sizeof( n ) );
         return from( n );
      }
   };

}  // namespace tao::pegtl::internal

#if defined( _WIN32 ) && !defined( __MINGW32__ ) && !defined( __CYGWIN__ )
#include "endian_win.hpp"
#else
#include "endian_gcc.hpp"
#endif

#endif
