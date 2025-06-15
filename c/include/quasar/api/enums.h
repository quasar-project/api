#pragma once

#include <quasar/api/detail/definitions.h>

QUASAR_C_API_BEGIN

#include <string.h>

/**
 * @brief Possible types of DSP backends for QuaSAR.
 */
enum quasar_dsp_backend {
  /**
   * @brief Basic DSP backend using CPU & FFTW3 library.
   * @details Used by default.
   */
  QUASAR_DSP_BACKEND_BASIC = 0,

  /**
   * @brief DSP backend using CUDA for GPU acceleration.
   * @details Uses hardware acceleration and allows for much faster processing of large datasets.
   * @note Requires NVIDIA GPU and CUDA toolkit installed.
   * Supported CUDA gencodes:
   * - CUDA 7.2 (__NVidia Jetson Xavier__)
   * - CUDA 8.6 (__NVidia Jetson AGX Orin__)
   * - CUDA 8.7 (__NVidia Jetson Orin Nano__)
   */
  QUASAR_DSP_BACKEND_CUDA = 1,

  /**
   * @brief Undefined DSP backend.
   * @details Used when the backend is not set or recognized.
   */
  QUASAR_DSP_BACKEND_UNDEFINED = 255
};

static inline char const* quasar_dsp_backend_name(enum quasar_dsp_backend backend) {
  switch(backend) {
    case QUASAR_DSP_BACKEND_BASIC: return "Basic";
    case QUASAR_DSP_BACKEND_CUDA: return "CUDA";
    case QUASAR_DSP_BACKEND_UNDEFINED: return "Undefined";
    default: return "Unknown";
  }
}

/**
 * @brief Window functions used in QuaSAR.
 */
enum quasar_window_function {
  QUASAR_WINDOW_FUNCTION_HAMMING = 0,     ///< Hamming window function.
  QUASAR_WINDOW_FUNCTION_BLACKMAN = 1,    ///< Blackman window function.
  QUASAR_WINDOW_FUNCTION_NUTTALL = 2,     ///< Nuttall window function.
  QUASAR_WINDOW_FUNCTION_UNDEFINED = 255  ///< Undefined window function.
};

static inline char const* quasar_window_function_name(enum quasar_window_function window) {
  switch(window) {
    case QUASAR_WINDOW_FUNCTION_HAMMING: return "Hamming";
    case QUASAR_WINDOW_FUNCTION_BLACKMAN: return "Blackman";
    case QUASAR_WINDOW_FUNCTION_NUTTALL: return "Nuttall";
    case QUASAR_WINDOW_FUNCTION_UNDEFINED: return "Undefined";
    default: return "Unknown";
  }
}

/**
 * @brief Output image formats for QuaSAR.
 */
enum quasar_image_format {
  QUASAR_IMAGE_FORMAT_PNG = 0,         ///< PNG image format.
  QUASAR_IMAGE_FORMAT_JPEG = 1,        ///< JPEG image format.
  QUASAR_IMAGE_FORMAT_UNDEFINED = 255  ///< Undefined image format.
};

static inline char const* quasar_image_format_name(enum quasar_image_format format) {
  switch(format) {
    case QUASAR_IMAGE_FORMAT_PNG: return "PNG";
    case QUASAR_IMAGE_FORMAT_JPEG: return "JPEG";
    case QUASAR_IMAGE_FORMAT_UNDEFINED: return "Undefined";
    default: return "Unknown";
  }
}

/**
 * @brief Underlying types of images in QuaSAR.
 * @details These types represent the data format of the image pixels.
 */
enum quasar_image_underlying_type {
  QUASAR_IMAGE_UNDERLYING_TYPE_UNSIGNED_8_BIT = 0,        ///< Unsigned 8-bit integer type.
  QUASAR_IMAGE_UNDERLYING_TYPE_SIGNED_16_BIT = 1,         ///< Signed 16-bit integer type.
  QUASAR_IMAGE_UNDERLYING_TYPE_FLOAT_32_BIT = 2,          ///< 32-bit floating point type.
  QUASAR_IMAGE_UNDERLYING_TYPE_COMPLEX_FLOAT_64_BIT = 3,  ///< 64-bit complex floating point type.
  QUASAR_IMAGE_UNDERLYING_TYPE_UNDEFINED = 255            ///< Undefined underlying type.
};

static inline char const* quasar_image_underlying_type_name(
  enum quasar_image_underlying_type type
) {
  switch(type) {
    case QUASAR_IMAGE_UNDERLYING_TYPE_UNSIGNED_8_BIT: return "Unsigned 8-bit";
    case QUASAR_IMAGE_UNDERLYING_TYPE_SIGNED_16_BIT: return "Signed 16-bit";
    case QUASAR_IMAGE_UNDERLYING_TYPE_FLOAT_32_BIT: return "32-bit Float";
    case QUASAR_IMAGE_UNDERLYING_TYPE_COMPLEX_FLOAT_64_BIT: return "64-bit Complex Float";
    case QUASAR_IMAGE_UNDERLYING_TYPE_UNDEFINED: return "Undefined";
    default: return "Unknown";
  }
}

static inline size_t quasar_image_underlying_type_size(enum quasar_image_underlying_type type) {
  switch(type) {
    case QUASAR_IMAGE_UNDERLYING_TYPE_UNSIGNED_8_BIT: return sizeof(uint8_t);
    case QUASAR_IMAGE_UNDERLYING_TYPE_SIGNED_16_BIT: return sizeof(int16_t);
    case QUASAR_IMAGE_UNDERLYING_TYPE_FLOAT_32_BIT: return sizeof(float);
    case QUASAR_IMAGE_UNDERLYING_TYPE_COMPLEX_FLOAT_64_BIT: return sizeof(float) * 2;
    case QUASAR_IMAGE_UNDERLYING_TYPE_UNDEFINED: return 0;
    default: return 0;
  }
}

/**
 * @brief Image kinds.
 */
enum quasar_image_kind {
  QUASAR_IMAGE_KIND_TELESCOPIC = 0,  ///< Image kind for telescopic (triangular) images.
  QUASAR_IMAGE_KIND_STRIP = 1,       ///< Image kind for strip (rectangular) images.
  QUASAR_IMAGE_KIND_UNDEFINED = 255  ///< Undefined image kind.
};

static inline char const* quasar_image_kind_name(enum quasar_image_kind kind) {
  switch(kind) {
    case QUASAR_IMAGE_KIND_TELESCOPIC: return "Telescopic";
    case QUASAR_IMAGE_KIND_STRIP: return "Strip";
    case QUASAR_IMAGE_KIND_UNDEFINED: return "Undefined";
    default: return "Unknown";
  }
}

QUASAR_C_API_END
