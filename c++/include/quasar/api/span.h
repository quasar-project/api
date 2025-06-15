/**
 * @file quasar/api/span.h
 * @brief `std::span` implementation compatible with C++14 and above.
 * @author Tristan Brindle
 * @copyright Distributed under the Boost Software License, Version 1.0.
 */

#pragma once

#include <quasar/api/detail/extern/span_impl.h>

namespace quasar {
  /**
   * @typedef span
   * @brief `std::span` implementation compatible with C++14 and above.
   * @sa https://en.cppreference.com/w/cpp/container/span
   */
#if defined(TCB_SPAN_NAMESPACE_NAME)
  using TCB_SPAN_NAMESPACE_NAME::span;
#else
#  error "Macro TCB_SPAN_NAMESPACE_NAME not found."
#endif  // defined(TCB_SPAN_NAMESPACE_NAME)
}  // namespace quasar
