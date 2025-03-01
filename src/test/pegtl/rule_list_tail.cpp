// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "verify_meta.hpp"
#include "verify_rule.hpp"

namespace tao::pegtl
{
   void unit_test()
   {
      verify_analyze< list_tail< opt< any >, opt< any > > >( __LINE__, __FILE__, false, true );
      verify_analyze< list_tail< opt< any >, any > >( __LINE__, __FILE__, false, false );
      verify_analyze< list_tail< any, opt< any > > >( __LINE__, __FILE__, true, false );
      verify_analyze< list_tail< any, any > >( __LINE__, __FILE__, true, false );

      verify_analyze< list_tail< opt< any >, opt< any >, opt< any > > >( __LINE__, __FILE__, false, true );
      verify_analyze< list_tail< opt< any >, opt< any >, any > >( __LINE__, __FILE__, false, true );
      verify_analyze< list_tail< opt< any >, any, opt< any > > >( __LINE__, __FILE__, false, true );
      verify_analyze< list_tail< opt< any >, any, any > >( __LINE__, __FILE__, false, false );
      verify_analyze< list_tail< any, opt< any >, opt< any > > >( __LINE__, __FILE__, true, true );
      verify_analyze< list_tail< any, opt< any >, any > >( __LINE__, __FILE__, true, false );
      verify_analyze< list_tail< any, any, opt< any > > >( __LINE__, __FILE__, true, true );
      verify_analyze< list_tail< any, any, any > >( __LINE__, __FILE__, true, false );

      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "", result_type::local_failure, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "b", result_type::local_failure, 1 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, ",", result_type::local_failure, 1 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, ",a", result_type::local_failure, 2 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "a,", result_type::success, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "a", result_type::success, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "a,a", result_type::success, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "a,b", result_type::success, 1 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "a,a,a", result_type::success, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "a,a,a,", result_type::success, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "a,a,a,a", result_type::success, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "a,a,a,b", result_type::success, 1 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "a,a,a,,", result_type::success, 1 );

      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "a ", result_type::success, 1 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, " a", result_type::local_failure, 2 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "a ,a", result_type::success, 3 );
      verify_rule< list_tail< one< 'a' >, one< ',' > > >( __LINE__, __FILE__, "a, a", result_type::success, 2 );

      verify_rule< list_tail< one< 'a' >, one< ',' >, blank > >( __LINE__, __FILE__, "", result_type::local_failure, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' >, blank > >( __LINE__, __FILE__, " ", result_type::local_failure, 1 );
      verify_rule< list_tail< one< 'a' >, one< ',' >, blank > >( __LINE__, __FILE__, ",", result_type::local_failure, 1 );
      verify_rule< list_tail< one< 'a' >, one< ',' >, blank > >( __LINE__, __FILE__, "a ", result_type::success, 1 );
      verify_rule< list_tail< one< 'a' >, one< ',' >, blank > >( __LINE__, __FILE__, " a", result_type::local_failure, 2 );
      verify_rule< list_tail< one< 'a' >, one< ',' >, blank > >( __LINE__, __FILE__, "a ,a", result_type::success, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' >, blank > >( __LINE__, __FILE__, "a, a", result_type::success, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' >, blank > >( __LINE__, __FILE__, "a, a,", result_type::success, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' >, blank > >( __LINE__, __FILE__, "a, a ,", result_type::success, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' >, blank > >( __LINE__, __FILE__, "a   ,   a    ,", result_type::success, 0 );
      verify_rule< list_tail< one< 'a' >, one< ',' >, blank > >( __LINE__, __FILE__, "a   ,   a    , ", result_type::success, 1 );
      verify_rule< list_tail< one< 'a' >, one< ',' >, blank > >( __LINE__, __FILE__, " a , a ", result_type::local_failure, 7 );
   }

}  // namespace tao::pegtl

#include "main.hpp"
