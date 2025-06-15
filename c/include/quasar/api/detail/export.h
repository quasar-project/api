#pragma once

// NOLINTBEGIN(*-reserved-identifier, *-identifier-naming, *-macro-usage)

#if defined(DOXYGEN)
#  define QUASAR_C_API
#else
#  if defined(_WIN32)
#    if defined(QUASAR_API_C_LIBRARY)
#      define QUASAR_C_API __declspec(dllexport)
#    elif defined(QUASAR_API_C_STATIC_LIBRARY)
#      define QUASAR_C_API
#    else
#      define QUASAR_C_API __declspec(dllimport)
#    endif
#  else
#    define QUASAR_C_API
#  endif
#endif

// NOLINTEND(*-reserved-identifier, *-identifier-naming, *-macro-usage)
