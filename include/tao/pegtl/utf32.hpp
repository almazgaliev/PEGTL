// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_UTF32_HPP
#define TAO_PEGTL_UTF32_HPP

#include "internal/peek_utf32.hpp"
#include "internal/result_on_found.hpp"
#include "internal/rules.hpp"

namespace tao::pegtl
{
   namespace utf32_be
   {
      // clang-format off
      struct any : internal::any< internal::peek_utf32_be > {};
      struct bom : internal::one< internal::result_on_found::success, internal::peek_utf32_be, 0xfeff > {};
      template< unsigned Count > struct many : internal::many< Count, internal::peek_utf32_be > {};
      template< char32_t... Cs > struct not_one : internal::one< internal::result_on_found::failure, internal::peek_utf32_be, Cs... > {};
      template< char32_t Lo, char32_t Hi > struct not_range : internal::range< internal::result_on_found::failure, internal::peek_utf32_be, Lo, Hi > {};
      template< char32_t... Cs > struct one : internal::one< internal::result_on_found::success, internal::peek_utf32_be, Cs... > {};
      template< char32_t Lo, char32_t Hi > struct range : internal::range< internal::result_on_found::success, internal::peek_utf32_be, Lo, Hi > {};
      template< char32_t... Cs > struct ranges : internal::ranges< internal::peek_utf32_be, Cs... > {};
      template< char32_t... Cs > struct string : internal::seq< internal::one< internal::result_on_found::success, internal::peek_utf32_be, Cs >... > {};
      // clang-format on

   }  // namespace utf32_be

   namespace utf32_le
   {
      // clang-format off
      struct any : internal::any< internal::peek_utf32_le > {};
      struct bom : internal::one< internal::result_on_found::success, internal::peek_utf32_le, 0xfeff > {};
      template< unsigned Count > struct many : internal::many< Count, internal::peek_utf32_le > {};
      template< char32_t... Cs > struct not_one : internal::one< internal::result_on_found::failure, internal::peek_utf32_le, Cs... > {};
      template< char32_t Lo, char32_t Hi > struct not_range : internal::range< internal::result_on_found::failure, internal::peek_utf32_le, Lo, Hi > {};
      template< char32_t... Cs > struct one : internal::one< internal::result_on_found::success, internal::peek_utf32_le, Cs... > {};
      template< char32_t Lo, char32_t Hi > struct range : internal::range< internal::result_on_found::success, internal::peek_utf32_le, Lo, Hi > {};
      template< char32_t... Cs > struct ranges : internal::ranges< internal::peek_utf32_le, Cs... > {};
      template< char32_t... Cs > struct string : internal::seq< internal::one< internal::result_on_found::success, internal::peek_utf32_le, Cs >... > {};
      // clang-format on

   }  // namespace utf32_le

   namespace utf32 = TAO_PEGTL_ENDIAN_SUFFIXED( utf32_ );

}  // namespace tao::pegtl

#endif
