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

namespace primordialmachine {

struct error_position
{
private:
  const char* m_file;

  int m_line;

public:
  constexpr error_position(const char* file, int line)
    : m_file(file)
    , m_line(line)
  {}

  constexpr const char* file() const { return m_file; }

  constexpr int line() const { return m_line; }

}; // struct error_position

} // namespace primordialmachine

#define PRIMORDIALMACHINE_ERROR_POSITION()                                     \
  primordialmachine::error_position(__FILE__, __LINE__)
