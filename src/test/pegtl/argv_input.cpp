// Copyright (c) 2017-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <cstring>

#include "test.hpp"

namespace tao::pegtl
{
   void unit_test()
   {
      char data[ 12 ];
      std::memcpy( data, "foo\0bar\0baz", 12 );
      char* argv[] = { data, data + 4, data + 8 };
      internal::fake_buffer_input< internal::argv_input > in( argv, 1 );
      //      TAO_PEGTL_TEST_ASSERT( in.source() == "argv[1]" );
      const auto result = parse< string< 'b', 'a', 'r' > >( in );
      TAO_PEGTL_TEST_ASSERT( result );
   }

}  // namespace tao::pegtl

#include "main.hpp"
