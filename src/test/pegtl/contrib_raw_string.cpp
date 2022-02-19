// Copyright (c) 2016-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "verify_meta.hpp"

#include <tao/pegtl/contrib/raw_string.hpp>

namespace tao::pegtl
{
   std::string content;

   using rstring = raw_string< '[', '=', ']' >;
   using qstring = raw_string< '[', '=', ']', alpha, digit >;

   template< typename Rule >
   struct raction
   {};

   template<>
   struct raction< rstring::content >
   {
      template< typename ActionInput, typename... States >
      static void apply( const ActionInput& in, const States&... /*unused*/ )
      {
         content.assign( in.begin(), in.end() );
      }
   };

   template< typename Rule >
   struct qaction
   {};

   template<>
   struct qaction< qstring::content >
   {
      template< typename ActionInput, typename... States >
      static void apply( const ActionInput& in, const States&... /*unused*/ )
      {
         content.assign( in.begin(), in.end() );
      }
   };

   struct rgrammar
      : seq< rstring, eof >
   {};

   struct qgrammar
      : seq< qstring, eof >
   {};

   template< typename Rule, template< typename > class Action, unsigned M, unsigned N >
   void verify_data( const std::size_t line, const char* file, const char ( &m )[ M ], const char ( &n )[ N ] )
   {
      content.clear();
      using pos_t = internal::selected_text_position< std::size_t >;
      internal::fake_buffer_input< internal::initialized_eager_position_input< pos_t, internal::line_based_input< lf_crlf, internal::memory_input< char > > > > in( pos_t( line, 1 ), m, m + M - 1 );
      const auto r = parse< Rule, Action >( in );
      if( ( !r ) || ( content != std::string_view( n, N - 1 ) ) ) {
         TAO_PEGTL_TEST_FAILED( "input data [ '" << m << "' ] expected success with [ '" << n << "' ] but got [ '" << content << "' ] result [ " << r << " ]" );  // LCOV_EXCL_LINE
      }
      content.clear();
      internal::fake_buffer_input< internal::initialized_lazy_position_input< pos_t, internal::line_based_input< lf_crlf, internal::memory_input< char > > > > in2( pos_t( line, 1 ), m, m + M - 1 );
      const auto r2 = parse< Rule, Action >( in2 );
      if( ( !r2 ) || ( content != std::string_view( n, N - 1 ) ) ) {
         TAO_PEGTL_TEST_FAILED( "input data [ '" << m << "' ] with tracking_mode::lazy expected success with [ '" << n << "' ] but got [ '" << content << "' ] result [ " << r2 << " ]" );  // LCOV_EXCL_LINE
      }
   }

   template< typename Rule >
   void verify_fail( const std::size_t line, const char* file, const std::string& s )
   {
      internal::fake_buffer_input< internal::line_based_input< lf, internal::memory_input< char > > > in( s );
      if( parse< Rule >( in ) ) {
         TAO_PEGTL_TEST_FAILED( "expected exception" );  // LCOV_EXCL_LINE
      }
   }

   void unit_test()
   {
      verify_analyze< rstring >( __LINE__, __FILE__, true, false );
      verify_analyze< qstring >( __LINE__, __FILE__, true, false );

      verify_analyze< raw_string< 'a', 'b', 'c', star< star< any > > > >( __LINE__, __FILE__, true, true );

      verify_data< rgrammar, raction >( __LINE__, __FILE__, "[[]]", "" );
      verify_data< rgrammar, raction >( __LINE__, __FILE__, "[[foo]]", "foo" );
      verify_data< rgrammar, raction >( __LINE__, __FILE__, "[===[foo]===]", "foo" );
      verify_data< rgrammar, raction >( __LINE__, __FILE__, "[===[\nfoo]===]", "foo" );
      verify_data< rgrammar, raction >( __LINE__, __FILE__, "[===[\r\nfoo]===]", "foo" );
      verify_data< rgrammar, raction >( __LINE__, __FILE__, "[===[\0\0\0]===]", "\0\0\0" );

      verify_data< qgrammar, qaction >( __LINE__, __FILE__, "[[]]", "" );
      verify_data< qgrammar, qaction >( __LINE__, __FILE__, "[[a1]]", "a1" );
      verify_data< qgrammar, qaction >( __LINE__, __FILE__, "[===[a1]===]", "a1" );
      verify_data< qgrammar, qaction >( __LINE__, __FILE__, "[===[\na1]===]", "a1" );
      verify_data< qgrammar, qaction >( __LINE__, __FILE__, "[===[\r\na1]===]", "a1" );
      verify_data< qgrammar, qaction >( __LINE__, __FILE__, "[===[a0a1a2a3]===]", "a0a1a2a3" );

      verify_fail< rgrammar >( __LINE__, __FILE__, "" );
      verify_fail< rgrammar >( __LINE__, __FILE__, "[" );
      verify_fail< rgrammar >( __LINE__, __FILE__, "[=" );
      verify_fail< rgrammar >( __LINE__, __FILE__, "[=[" );
      verify_fail< rgrammar >( __LINE__, __FILE__, "[=[]=" );
      verify_fail< rgrammar >( __LINE__, __FILE__, "[=[]]" );
      verify_fail< rgrammar >( __LINE__, __FILE__, "[]" );
      verify_fail< rgrammar >( __LINE__, __FILE__, "[[]] " );
      verify_fail< rgrammar >( __LINE__, __FILE__, " [[]]" );
      verify_fail< rgrammar >( __LINE__, __FILE__, "[=[]-]" );
      verify_fail< rgrammar >( __LINE__, __FILE__, "[-[]=]" );
      verify_fail< rgrammar >( __LINE__, __FILE__, "[-[]-]" );
      verify_fail< rgrammar >( __LINE__, __FILE__, "[===[]====]" );
      verify_fail< rgrammar >( __LINE__, __FILE__, "[====[]===]" );

      verify_fail< qgrammar >( __LINE__, __FILE__, "" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[=" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[=[" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[=[]=" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[=[]]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[[]] " );
      verify_fail< qgrammar >( __LINE__, __FILE__, " [[]]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[=[]-]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[-[]=]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[-[]-]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[===[]====]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[====[]===]" );

      verify_fail< qgrammar >( __LINE__, __FILE__, "[=[-]=]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[=[1]=]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[=[a]=]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[=[a+]=]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[=[aa]=]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[=[11]=]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[=[a1a]=]" );
      verify_fail< qgrammar >( __LINE__, __FILE__, "[=[a1aa]=]" );
   }

}  // namespace tao::pegtl

#include "main.hpp"
