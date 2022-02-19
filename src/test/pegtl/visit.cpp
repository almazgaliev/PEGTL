// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <vector>

#include "test.hpp"

namespace tao::pegtl
{
   static_assert( !internal::contains_v< int > );
   static_assert( internal::contains_v< int, char, double, int > );
   static_assert( !internal::contains_v< int, char, double, unsigned > );

   static_assert( std::is_same_v< internal::filter_t< type_list< int, char, float, double >, empty_list, empty_list >, type_list< int, char, float, double > > );
   static_assert( std::is_same_v< internal::filter_t< type_list< int, char, float, double >, empty_list, type_list< char, double > >, type_list< int, float > > );

   using grammar = seq< plus< alpha >, star< sor< space, digit > > >;

   template< typename Name >
   struct visitor
   {
      static void visit( std::vector< std::string >& names )
      {
         names.emplace_back( demangle< Name >() );
      }
   };

   void unit_test()
   {
      std::vector< std::string > names;
      visit< grammar, visitor >( names );
      TAO_PEGTL_TEST_ASSERT( names.size() == 7 );
   }

}  // namespace tao::pegtl

#include "main.hpp"
