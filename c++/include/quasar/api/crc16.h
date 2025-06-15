#pragma once

#include <array>
#include <limits>
#include <stdexcept>
#include <quasar/api/span.h>
#include <quasar/api/detail/export.h>

namespace quasar {
  template <typename D, typename S>
  [[nodiscard]] D byte_cast(S const* source) {
    if(source == nullptr)
      throw std::invalid_argument("byte_cast: source cannot be null");
    auto dest = D();
    std::memcpy(
      &dest,
      reinterpret_cast<void const*>(source),  // NOLINT(*-pro-type-reinterpret-cast)
      sizeof dest
    );
    return dest;
  }

  [[nodiscard]] QUASAR_API std::uint16_t crc16(std::byte const* data, std::size_t size) noexcept;
  [[nodiscard]] QUASAR_API std::uint16_t crc16(span<std::byte const> data) noexcept;
  [[nodiscard]] QUASAR_API std::uint16_t crc16_ccitt(std::byte const* data, std::size_t size) noexcept;
  [[nodiscard]] QUASAR_API std::uint16_t crc16_ccitt(span<std::byte const> data) noexcept;
}  // namespace quasar
