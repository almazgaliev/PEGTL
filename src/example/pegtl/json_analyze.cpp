// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/json.hpp>

namespace pegtl = tao::pegtl;

namespace example
{
   using grammar = pegtl::seq< pegtl::json::text, pegtl::eof >;

}  // namespace example

int main()  // NOLINT(bugprone-exception-escape)
{
   if( pegtl::analyze< example::grammar >( std::cout ) != 0 ) {
      std::cout << "cycles without progress detected!" << std::endl;
      return 1;
   }
   return 0;
}
