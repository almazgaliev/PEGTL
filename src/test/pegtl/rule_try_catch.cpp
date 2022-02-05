// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#if !defined( __cpp_exceptions )
#include <iostream>
int main()
{
   std::cout << "Exception support disabled, skipping test..." << std::endl;
}
#else

#include "test.hpp"
#include "verify_seqs.hpp"

namespace tao::pegtl
{
   template< typename... Rules >
   using test_try_catch_rule = try_catch_return_false< must< Rules... > >;

   void unit_test()
   {
      verify_seqs< try_catch_return_false >();
      verify_seqs< test_try_catch_rule >();
   }

}  // namespace tao::pegtl

#include "main.hpp"

#endif
