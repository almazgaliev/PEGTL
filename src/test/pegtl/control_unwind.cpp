// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#if !defined( __cpp_exceptions )
#include <iostream>
int main()
{
   std::cout << "Exception support disabled, skipping test..." << std::endl;
}
#else

#include <tao/pegtl.hpp>

#include "test.hpp"

namespace tao::pegtl
{
   struct r
      : seq< alpha, digit >
   {};

   template< typename R >
   struct a
      : nothing< R >
   {};

   template< typename R >
   struct c
      : normal< R >
   {};

   unsigned flags = 0;

   template<>
   struct a< alpha >
   {
      static void apply0()
      {
         flags |= 1;
      }
   };

   template<>
   struct a< digit >
   {
      static void apply0()
      {
         throw 42;
      }
   };

   template<>
   struct c< r >
      : normal< r >
   {
      template< typename Input >
      static void unwind( const Input& /*unused*/ )
      {
         flags |= 2;
      }
   };

   void unit_test()
   {
      memory_input in( "a1", __FUNCTION__ );
      try {
         parse< r, a, c >( in );
         TAO_PEGTL_TEST_UNREACHABLE;  // LCOV_EXCL_LINE
      }
      catch( const int& e ) {
         TAO_PEGTL_TEST_ASSERT( e == 42 );
      }
      TAO_PEGTL_TEST_ASSERT( flags == 3 );
   }

}  // namespace tao::pegtl

#include "main.hpp"

#endif
