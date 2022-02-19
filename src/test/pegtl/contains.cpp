// Copyright (c) 2021-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <type_traits>

#include "test.hpp"

namespace tao::pegtl
{
   // clang-format off
   struct A : plus< alpha, opt< A > > {};
   struct B : star< sor< space, digit, A > > {};
   struct grammar : seq< A, B > {};
   // clang-format on

   void unit_test()
   {
      static_assert( grammar_contains_rule< grammar, digit > );
      static_assert( !grammar_contains_rule< grammar, xdigit > );
   }

}  // namespace tao::pegtl

#include "main.hpp"
