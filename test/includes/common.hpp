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
