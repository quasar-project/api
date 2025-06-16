#pragma once

#include <array>
#include <chrono>
#include <memory>
#include <string>
#include <string_view>
#include <quasar/api/detail/export.h>
#include <quasar/api/span.h>
#include <quasar/api/enums.h>

extern "C"
{
  struct quasar_image_metadata;
}

namespace quasar {
  class QUASAR_API ImageMetadata {
   public:
    ImageMetadata();
    ImageMetadata(ImageMetadata const&);
    ImageMetadata& operator=(ImageMetadata const&);
    ImageMetadata(ImageMetadata&&) noexcept;
    ImageMetadata& operator=(ImageMetadata&&) noexcept;
    ~ImageMetadata();

    [[nodiscard]] double latitude() const noexcept;
    void set_latitude(double latitude) noexcept;

    [[nodiscard]] double longitude() const noexcept;
    void set_longitude(double longitude) noexcept;

    [[nodiscard]] float altitude() const noexcept;
    void set_altitude(float altitude) noexcept;

    [[nodiscard]] float velocity() const noexcept;
    void set_velocity(float velocity) noexcept;

    [[nodiscard]] float near_edge() const noexcept;
    void set_near_edge(float near_edge) noexcept;

    [[nodiscard]] float frame_shift() const noexcept;
    void set_frame_shift(float frame_shift) noexcept;

    [[nodiscard]] float width() const noexcept;
    void set_width(float width) noexcept;

    [[nodiscard]] float height() const noexcept;
    void set_height(float height) noexcept;

    [[nodiscard]] float dx() const noexcept;
    void set_dx(float dx) noexcept;

    [[nodiscard]] float dy() const noexcept;
    void set_dy(float dy) noexcept;

    [[nodiscard]] float angle() const noexcept;
    void set_angle(float angle) noexcept;

    [[nodiscard]] float drift_angle() const noexcept;
    void set_drift_angle(float drift_angle) noexcept;

    [[nodiscard]] std::chrono::duration<double> time_offset() const noexcept;
    void set_time_offset(std::chrono::duration<double> const& offset) noexcept;

    [[nodiscard]] std::chrono::duration<double> time_duration() const noexcept;
    void set_time_duration(std::chrono::duration<double> const& duration) noexcept;

    [[nodiscard]] std::chrono::system_clock::time_point timestamp() const noexcept;
    void set_timestamp(std::chrono::system_clock::time_point timestamp) noexcept;

    [[nodiscard]] ImageKind kind() const noexcept;
    void set_kind(ImageKind kind) noexcept;

    [[nodiscard]] std::array<std::uint16_t, 3> library_version() const noexcept;
    void set_library_version(std::array<std::uint16_t, 3> const& version) noexcept;

    [[nodiscard]] std::uint8_t sar_mode() const noexcept;
    void set_sar_mode(std::uint8_t sar_mode) noexcept;

    [[nodiscard]] float divergence_angle() const noexcept;
    void set_divergence_angle(float divergence_angle) noexcept;

    [[nodiscard]] float frequency_interpolation_coefficient() const noexcept;
    void set_frequency_interpolation_coefficient(float fic) noexcept;

    [[nodiscard]] std::uint16_t crc16() const noexcept;
    void set_crc16(std::uint16_t crc16) noexcept;

    [[nodiscard]] std::uint16_t calculate_checksum() const noexcept;

    [[nodiscard]] nlohmann::json to_json() const;
    [[nodiscard]] std::string to_json_string(std::size_t indent = 2) const;

    [[nodiscard]] static ImageMetadata from_json(nlohmann::json const& json);
    [[nodiscard]] static ImageMetadata from_json_string(std::string_view json);

    [[nodiscard]] static ImageMetadata from_exif_bytes(span<std::byte const> exif);

   private:
    explicit ImageMetadata(quasar_image_metadata data);

    [[nodiscard]] static ImageMetadata from_legacy_json(nlohmann::json const& json);

    std::unique_ptr<quasar_image_metadata> d_;
  };
}  // namespace quasar
