# Primordial Machine's Error Library
C++ 17 library providing extendable error objects and exceptions. 
The library is made available publicly on [GitHub](https://github.com/primordialmachine/error) under the [MIT License](https://github.com/primordialmachine/error/blob/master/LICENSE),

## Restrictions
*The library officially only supports Visual Studio 2017.*

## Usage Example
The folder [example](https://github.com/primordialmachine/error/blob/master/example) contains example programs.

## Creating the library with Visual Studio 2017
- Open the solution `error.sln` in Microsoft Visual Studio 2017.
- Batch build everything.
- The folder `packages` contains the distribution of the library i.e. include files and the static libraries for
  - the platforms `Win32` and `x64` and
   - configurations `Release` and `Debug`.
- Copy the contents of the `packages` folder into a directory. Let `[library home]` be a placeholder denoting the path by which that folder can be referenced from your project. 
- Add
  - the include path `[library home]/primordialmachine/error/${Platform.toLower()}/{Configuration.toLower()}/includes` and
  - the library path `[library home]/primordialmachine/error/${Platform.toLower()}/{Configuration.toLower()}/libraries` to your project.
- Link your project with the library `error.lib`.
- Add the include directive `#include "primordialmachine/error/include.hpp"` where appropriate.
- You can now use the functionality provided by the library.

## Library Interface Documentation
## `namespace primordialmachine`
The namespace this library is adding its declarations/definitions to.
The added namespace elements are documented below.

## `PRIMORDIALMACHINE_ERROR_LOCATION`
A macro evaluating to an `error_location` object with the file name and line number of the location within the C++ program at which the macro was evaluated.

## `class error_position { ... }`
Objects of type `error_position` represent locations in a C++ program in terms of the name of a source file and the line number of a line in that source file. `error_position` is nothrow (copy|move) (constructible|assignable).
### Constructors
- `constexpr error_position(const char *file, int line)`
   Construct this `error_position` object.
   - `file` is a pointer to a static constant string denoting the name of the C++ source file.
   - `line` is a non-negative `int` value denoting the line in the C++ source file.
### Methods
- `constexpr const char *file() const`
   A pointer to a static constant string denoting the name of the C++ source file.
- `constexpr int line() const`
   A positive `int` value denoting the line in the C++ source file.

## `class error { ... }`
The base class from which to derive custom error types.
### Type definitions
- `using message_type = ...`
An alias for `std::string` (v1.0).
- `using position_type = ...`
An alias for `primordialmachine::error_position` (v1.0).
### Constructors
- `error(message_type message, position_type position)`
Construct this error object.
- `message`: The message of the error.
- `position`: The position associated with the error.
### Methods
- `constexpr message_type& message() const`
   Get the message of the error.
- `constexpr position_type& position() const`
  Get the position of the error.
- `void raise() const`
   Raise an `exception` wrapping a clone of this `error` object..
- `error_ptr clone() const`
  Return an `error_ptr` to a clone of this `error` object.
- `virtual error *clone_implementation() const`
   *To be overriden by descendant classes of `error`.*
   Returns a pointer to a clone of this `error` object.
   Exceptions raised by this function are propagated.

## `class error_exception`
Class derived from `std::exception` wrapping around an `error` or derived type object. `error_exception` is nothrow (copy/move) (assignable|constructible).
### Type definitions
- `using error_type = ...`
  An alias for `primordialmachine::error` (v1.0).
### Constructors
- `error_exception(const error_type& error)`
  Construct this `error_exception` object wrapping a clone of the `error_type` or derived type object.
### Methods
- `constexpr const std::shared_ptr<error_type>& error() const { ... }`
  Get the wrapped `error` or derived type object.
- `const char *what() const override` (inherited from `std::exception`)
  Return a pointer to the message of the wrapped `error` or derived type object.
