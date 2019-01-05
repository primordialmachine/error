///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Primordial Machine's Errors Library
// Copyright (c) 2017-2019 Michael Heilmann
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

#include "primordialmachine/errors/include.hpp"
#include "gtest/gtest.h"

class test_error;
class test_exception;

class test_exception : public primordialmachine::exception
{
public:
  test_exception(const test_error& error);
}; // class test_exception

class test_error : public primordialmachine::error
{
private:
  using parent_type = primordialmachine::error;

public:
  using position_type = primordialmachine::error_position;

  test_error(position_type position);

protected:
  test_error* clone_implementation() const;
  void raise_implementation() const;

private:
  static std::string build_message(const position_type& position)
  {
    std::ostringstream os;
    os << "file: " << position.file() << ","
       << "line:" << position.line() << ": "
       << "test error";
    return os.str();
  }

}; // class test_error

test_exception::test_exception(const test_error& error)
  : primordialmachine::exception(error)
{}

test_error::test_error(position_type position)
  : parent_type(build_message(position), position)
{}

test_error*
test_error::clone_implementation() const
{
  return new test_error(*this);
}

void
test_error::raise_implementation() const
{
  throw test_exception(*this);
}
