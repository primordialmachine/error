///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Primordial Machine's Error Library
// Copyright (C) 2017-2018 Michael Heilmann
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "primordialmachine/error/error.hpp"

namespace primordialmachine {

class error_exception : public std::exception
{
public:
  using error_type = primordialmachine::error;

  error_exception();

  error_exception(const error_type& error);

  constexpr const std::shared_ptr<error_type>& error() const { return m_error; }

  const char* what() const override;

private:
  std::shared_ptr<error_type> m_error;

}; // class error_exception

static_assert(std::is_nothrow_move_assignable_v<error_exception>,
              "error exception is supposed to be nothrow move assignable");
static_assert(std::is_nothrow_copy_assignable_v<error_exception>,
              "error_exception is supposed to be nothrow copy assignable");
static_assert(std::is_nothrow_move_constructible_v<error_exception>,
              "error_exception is supposed to be nothrow move constructible");
static_assert(std::is_nothrow_copy_constructible_v<error_exception>,
              "error_exception is suppposed to be nothrow copy constructible");

} // namespace primordialmachine
