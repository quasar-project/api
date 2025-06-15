#include <quasar/api/crc16.h>

#include <quasar/api/ffi/crc16.h>

namespace quasar {
  std::uint16_t crc16(std::byte const* data, std::size_t const size) noexcept {
    return ::quasar_crc16(reinterpret_cast<std::uint8_t const*>(data), size);
  }

  std::uint16_t crc16(span<std::byte const> const data) noexcept {
    return crc16(data.data(), data.size());
  }

  std::uint16_t crc16_ccitt(std::byte const* data, std::size_t const size) noexcept {
    return ::quasar_crc16_ccitt(reinterpret_cast<std::uint8_t const*>(data), size);
  }

  std::uint16_t crc16_ccitt(span<std::byte const> const data) noexcept {
    return crc16_ccitt(data.data(), data.size());
  }
}  // namespace quasar
