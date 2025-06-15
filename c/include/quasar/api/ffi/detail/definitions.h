#pragma once

#ifdef __cplusplus
#  define QUASAR_C_API_BEGIN extern "C" {
#  define QUASAR_C_API_END }
#else
#  define QUASAR_C_API_BEGIN
#  define QUASAR_C_API_END
#endif

#include <stdint.h>
#include <stddef.h>
#include <quasar/api/ffi/detail/export.h>