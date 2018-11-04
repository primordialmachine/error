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

#include "primordialmachine/error/error_position.hpp"
#include <string>
#include <type_traits>

namespace primordialmachine {

struct error
{
protected:
  using message_type = std::string;
  using position_type = error_position;

  // A constant expression boolean value indicating wether
  // error(message, position)
  // is
  // nothrow constructible.
  static constexpr bool is_nothrow_constructible_v =
    std::is_nothrow_move_constructible_v<message_type> &&
    std::is_nothrow_move_constructible_v<position_type>;

  error(message_type message,
        position_type position) noexcept(error::is_nothrow_constructible_v);

  // A constant expression boolean value indicating wether
  // error(const error&)
  // is
  // nothrow copy constructible.
  static constexpr bool is_nothrow_copy_constructible_v =
    std::is_nothrow_copy_constructible_v<message_type> &&
    std::is_nothrow_copy_constructible_v<position_type>;

  error(const error& other) noexcept(error::is_nothrow_copy_constructible_v);

  virtual error* clone_implementation() const = 0;

public:
  constexpr const message_type& message() const { return m_message; }

  constexpr const position_type& position() const { return m_position; }

  void raise() const;

private:
  friend class error_exception;

  message_type m_message;

  position_type m_position;

}; // struct error

template<typename ERROR>
using is_error = std::conjunction<std::is_copy_constructible<ERROR>,
                                  std::is_copy_assignable<ERROR>>;

template<typename ERROR>
inline constexpr bool is_error_v = is_error<ERROR>::value;

} // namespace engine
