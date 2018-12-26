#include "primordialmachine/errors/include.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdlib.h>

class file_not_found_error;
class file_not_found_error_exception;

class file_not_found_error_exception : public primordialmachine::exception
{
public:
  file_not_found_error_exception(const file_not_found_error& error);
};

// Provides the path of the file which was not found.
class file_not_found_error : public primordialmachine::error
{
private:
  using parent_type = primordialmachine::error;

public:
  using position_type = primordialmachine::error_position;

  using path_type = std::filesystem::path;

  file_not_found_error(const file_not_found_error& other);

  file_not_found_error(position_type position, path_type path);

  constexpr const path_type& path() const { return m_path; }

protected:
  file_not_found_error* clone_implementation() const;
  void raise_implementation() const;

private:
  static std::string build_message(const position_type& position,
                                   const path_type& path)
  {
    std::ostringstream os;
    os << "file: " << position.file() << ","
       << "line:" << position.line() << ": "
       << "file `" << path.string() << "` not found";
    return os.str();
  }

  path_type m_path;

}; // class file_not_found_error

file_not_found_error_exception::file_not_found_error_exception(
  const file_not_found_error& error)
  : primordialmachine::exception(error)
{}

file_not_found_error::file_not_found_error(const file_not_found_error& other)
  : parent_type(other)
  , m_path(other.path())
{}

file_not_found_error::file_not_found_error(position_type position,
                                           path_type path)
  : parent_type(build_message(position, path), position)
  , m_path(path)
{}

file_not_found_error*
file_not_found_error::clone_implementation() const
{
  return new file_not_found_error(*this);
}

void
file_not_found_error::raise_implementation() const
{
  throw file_not_found_error_exception(*this);
}

int
main()
{
  try {
    file_not_found_error(PRIMORDIALMACHINE_ERROR_POSITION(),
                         std::filesystem::path("README.md"))
      .raise();
  } 
  catch (const file_not_found_error_exception& ex) {
    std::cerr << "file_not_found_error_exception: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch (const primordialmachine::exception& ex) {
    std::cerr << "primordialmachine::error_exception " << ex.what() << std::endl;
    return EXIT_FAILURE;
  } catch (...) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
