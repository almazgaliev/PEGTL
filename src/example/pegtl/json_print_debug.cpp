// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include <tao/pegtl/contrib/json.hpp>

int main()  // NOLINT(bugprone-exception-escape)
{
   tao::pegtl::print_debug< tao::pegtl::json::text >( std::cout );
   return 0;
}
