// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INT64_HPP
#define TAO_PEGTL_INT64_HPP

#include "internal/peek_int.hpp"
#include "internal/result_on_found.hpp"
#include "internal/rules.hpp"

namespace tao::pegtl
{
   namespace int64_be
   {
      // clang-format off
      struct any : internal::any< internal::peek_int64_be > {};
      template< unsigned Count > struct many : internal::many< Count, internal::peek_int64_be > {};

      template< std::int64_t... Cs > struct not_one : internal::one< internal::result_on_found::failure, internal::peek_int64_be, Cs... > {};
      template< std::int64_t Lo, std::int64_t Hi > struct not_range : internal::range< internal::result_on_found::failure, internal::peek_int64_be, Lo, Hi > {};
      template< std::int64_t... Cs > struct one : internal::one< internal::result_on_found::success, internal::peek_int64_be, Cs... > {};
      template< std::int64_t Lo, std::int64_t Hi > struct range : internal::range< internal::result_on_found::success, internal::peek_int64_be, Lo, Hi > {};
      template< std::int64_t... Cs > struct ranges : internal::ranges< internal::peek_int64_be, Cs... > {};
      template< std::int64_t... Cs > struct string : internal::seq< internal::one< internal::result_on_found::success, internal::peek_int64_be, Cs >... > {};
      // clang-format on

   }  // namespace int64_be

   namespace int64_le
   {
      // clang-format off
      struct any : internal::any< internal::peek_int64_le > {};
      template< unsigned Count > struct many : internal::many< Count, internal::peek_int64_le > {};

      template< std::int64_t... Cs > struct not_one : internal::one< internal::result_on_found::failure, internal::peek_int64_le, Cs... > {};
      template< std::int64_t Lo, std::int64_t Hi > struct not_range : internal::range< internal::result_on_found::failure, internal::peek_int64_le, Lo, Hi > {};
      template< std::int64_t... Cs > struct one : internal::one< internal::result_on_found::success, internal::peek_int64_le, Cs... > {};
      template< std::int64_t Lo, std::int64_t Hi > struct range : internal::range< internal::result_on_found::success, internal::peek_int64_le, Lo, Hi > {};
      template< std::int64_t... Cs > struct ranges : internal::ranges< internal::peek_int64_le, Cs... > {};
      template< std::int64_t... Cs > struct string : internal::seq< internal::one< internal::result_on_found::success, internal::peek_int64_le, Cs >... > {};
      // clang-format on

   }  // namespace int64_le

}  // namespace tao::pegtl

#endif
