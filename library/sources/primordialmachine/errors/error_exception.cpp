///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Primordial Machine's Errors Library
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

#include "primordialmachine/errors/error_exception.hpp"
#include "primordialmachine/errors/error.hpp"
#include <memory>

namespace primordialmachine {

error_exception::error_exception()
  : m_error(nullptr)
{
  throw std::bad_exception();
}

error_exception::error_exception(const error_type& error)
  // delete p is invoked if std::shared_ptr<error>(p) raises an exception.
  : m_error(std::shared_ptr<error_type>(error.clone_implementation()))
{}

const char*
error_exception::what() const
{
  return m_error->message().c_str();
}

} // namespace primordialmachine
