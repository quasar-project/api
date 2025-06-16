#pragma once

#include <fmt/format.h>
#include <quasar/api/ffi/enums.h>

namespace quasar {
  enum class DSPBackend {
    Basic = QUASAR_DSP_BACKEND_BASIC,
    CUDA = QUASAR_DSP_BACKEND_CUDA,
    Undefined = QUASAR_DSP_BACKEND_UNDEFINED
  };

  enum class WindowFunction {
    Hamming = QUASAR_WINDOW_FUNCTION_HAMMING,
    Blackman = QUASAR_WINDOW_FUNCTION_BLACKMAN,
    Nuttall = QUASAR_WINDOW_FUNCTION_NUTTALL,
    Undefined = QUASAR_WINDOW_FUNCTION_UNDEFINED
  };

  enum class ImageFormat {
    PNG = QUASAR_IMAGE_FORMAT_PNG,
    JPEG = QUASAR_IMAGE_FORMAT_JPEG,
    Undefined = QUASAR_IMAGE_FORMAT_UNDEFINED
  };

  enum class ImageUnderlyingType {
    Unsigned8Bit = QUASAR_IMAGE_UNDERLYING_TYPE_UNSIGNED_8_BIT,
    Signed16Bit = QUASAR_IMAGE_UNDERLYING_TYPE_SIGNED_16_BIT,
    Float32Bit = QUASAR_IMAGE_UNDERLYING_TYPE_FLOAT_32_BIT,
    ComplexFloat64Bit = QUASAR_IMAGE_UNDERLYING_TYPE_COMPLEX_FLOAT_64_BIT,
    Undefined = QUASAR_IMAGE_UNDERLYING_TYPE_UNDEFINED
  };

  enum class ImageKind {
    Telescopic = QUASAR_IMAGE_KIND_TELESCOPIC,
    Strip = QUASAR_IMAGE_KIND_STRIP,
    Undefined = QUASAR_IMAGE_KIND_UNDEFINED
  };

  [[nodiscard]] inline std::size_t size_of(ImageUnderlyingType const type) noexcept {
    return quasar_image_underlying_type_size(static_cast<quasar_image_underlying_type>(type));
  }
}  // namespace quasar

namespace fmt {
  template <>
  struct formatter<quasar::DSPBackend> : formatter<std::string> {
    template <typename Context>
    auto format(quasar::DSPBackend const backend, Context& ctx) const {
      return formatter<std::string>::format(
        quasar_dsp_backend_name(static_cast<quasar_dsp_backend>(backend)),
        ctx
      );
    }
  };

  template <>
  struct formatter<quasar::WindowFunction> : formatter<std::string> {
    template <typename Context>
    auto format(quasar::WindowFunction const function, Context& ctx) const {
      return formatter<std::string>::format(
        quasar_window_function_name(static_cast<quasar_window_function>(function)),
        ctx
      );
    }
  };

  template <>
  struct formatter<quasar::ImageFormat> : formatter<std::string> {
    template <typename Context>
    auto format(quasar::ImageFormat const format, Context& ctx) const {
      return formatter<std::string>::format(
        quasar_image_format_name(static_cast<quasar_image_format>(format)),
        ctx
      );
    }
  };

  template <>
  struct formatter<quasar::ImageUnderlyingType> : formatter<std::string> {
    template <typename Context>
    auto format(quasar::ImageUnderlyingType const type, Context& ctx) const {
      return formatter<std::string>::format(
        quasar_image_underlying_type_name(static_cast<quasar_image_underlying_type>(type)),
        ctx
      );
    }
  };

  template <>
  struct formatter<quasar::ImageKind> : formatter<std::string> {
    template <typename Context>
    auto format(quasar::ImageKind const kind, Context& ctx) const {
      return formatter<std::string>::format(
        quasar_image_kind_name(static_cast<quasar_image_kind>(kind)),
        ctx
      );
    }
  };
}  // namespace fmt
