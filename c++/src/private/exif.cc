#include <quasar/api/exif.h>

#include <vector>
#include <quasar/api/ffi/exif.h>

namespace quasar {
  ImageMetadata::ImageMetadata()
    : d_(std::make_unique<quasar_image_metadata>()) {
    ::quasar_image_metadata_init(d_.get());
  }

  ImageMetadata::~ImageMetadata() = default;

  double ImageMetadata::latitude() const noexcept { return d_->latitude; }

  void ImageMetadata::set_latitude(double const latitude) noexcept { d_->latitude = latitude; }

  double ImageMetadata::longitude() const noexcept { return d_->longitude; }

  void ImageMetadata::set_longitude(double const longitude) noexcept { d_->longitude = longitude; }

  float ImageMetadata::altitude() const noexcept { return d_->altitude; }

  void ImageMetadata::set_altitude(float const altitude) noexcept { d_->altitude = altitude; }

  float ImageMetadata::velocity() const noexcept { return d_->velocity; }

  void ImageMetadata::set_velocity(float const velocity) noexcept { d_->velocity = velocity; }

  float ImageMetadata::near_edge() const noexcept { return d_->x0; }

  void ImageMetadata::set_near_edge(float const near_edge) noexcept { d_->x0 = near_edge; }

  float ImageMetadata::frame_shift() const noexcept { return d_->y0; }

  void ImageMetadata::set_frame_shift(float const frame_shift) noexcept { d_->y0 = frame_shift; }

  float ImageMetadata::width() const noexcept { return d_->lx; }

  void ImageMetadata::set_width(float const width) noexcept { d_->lx = width; }

  float ImageMetadata::height() const noexcept { return d_->ly; }

  void ImageMetadata::set_height(float const height) noexcept { d_->ly = height; }

  float ImageMetadata::dx() const noexcept { return d_->dx; }

  void ImageMetadata::set_dx(float const dx) noexcept { d_->dx = dx; }

  float ImageMetadata::dy() const noexcept { return d_->dy; }

  void ImageMetadata::set_dy(float const dy) noexcept { d_->dy = dy; }

  float ImageMetadata::angle() const noexcept { return d_->angle; }

  void ImageMetadata::set_angle(float const angle) noexcept { d_->angle = angle; }

  float ImageMetadata::drift_angle() const noexcept { return d_->drift_angle; }

  void ImageMetadata::set_drift_angle(float const drift_angle) noexcept {
    d_->drift_angle = drift_angle;
  }

  std::chrono::duration<double> ImageMetadata::time_offset() const noexcept {
    return std::chrono::duration<double>(d_->time_offset);
  }

  void ImageMetadata::set_time_offset(std::chrono::duration<double> const& offset) noexcept {
    d_->time_offset = static_cast<float>(offset.count());
  }

  std::chrono::duration<double> ImageMetadata::time_duration() const noexcept {
    return std::chrono::duration<double>(d_->time_duration);
  }

  void ImageMetadata::set_time_duration(std::chrono::duration<double> const& duration) noexcept {
    d_->time_duration = static_cast<float>(duration.count());
  }

  ImageKind ImageMetadata::kind() const noexcept { return static_cast<ImageKind>(d_->kind); }

  void ImageMetadata::set_kind(ImageKind const kind) noexcept {
    d_->kind = static_cast<std::uint8_t>(kind);
  }

  std::array<std::uint16_t, 3> ImageMetadata::library_version() const noexcept {
    return {d_->library_version[0], d_->library_version[1], d_->library_version[2]};
  }

  void ImageMetadata::set_library_version(std::array<std::uint16_t, 3> const& version) noexcept {
    d_->library_version[0] = version[0];
    d_->library_version[1] = version[1];
    d_->library_version[2] = version[2];
  }

  std::uint8_t ImageMetadata::sar_mode() const noexcept { return d_->sar_mode; }

  void ImageMetadata::set_sar_mode(std::uint8_t const sar_mode) noexcept {
    d_->sar_mode = sar_mode;
  }

  float ImageMetadata::divergence_angle() const noexcept { return d_->divergence_angle; }

  void ImageMetadata::set_divergence_angle(float const divergence_angle) noexcept {
    d_->divergence_angle = divergence_angle;
  }

  float ImageMetadata::frequency_interpolation_coefficient() const noexcept { return d_->fic; }

  void ImageMetadata::set_frequency_interpolation_coefficient(float const fic) noexcept {
    d_->fic = fic;
  }

  std::uint16_t ImageMetadata::crc16() const noexcept { return d_->crc16; }

  void ImageMetadata::set_crc16(std::uint16_t const crc16) noexcept { d_->crc16 = crc16; }

  std::uint16_t ImageMetadata::calculate_checksum() const noexcept {
    return ::quasar_image_metadata_checksum(d_.get());
  }

  std::string ImageMetadata::to_json() const noexcept {
    auto buffer_size = static_cast<std::size_t>(512);
    auto buffer = std::vector<char>(buffer_size);

    while(true) {
      std::fill(buffer.begin(), buffer.end(), '\0');
      ::quasar_image_metadata_to_json(d_.get(), buffer.data(), buffer.size());

      if(auto const actual_len = ::strnlen(buffer.data(), buffer.size());
         actual_len < buffer.size() - 1)
        return std::string(buffer.data());

      buffer_size *= 2;
      buffer.resize(buffer_size);
    }
  }

  ImageMetadata ImageMetadata::from_json(std::string const& json) noexcept {
    return ImageMetadata(::quasar_image_metadata_from_json(json.data(), json.size()));
  }

  ImageMetadata ImageMetadata::from_exif_bytes(span<std::byte const> const exif) noexcept {
    return ImageMetadata(
      ::quasar_image_metadata_from_exif(
        reinterpret_cast<std::uint8_t const*>(exif.data()),
        exif.size()
      )
    );
  }

  ImageMetadata::ImageMetadata(quasar_image_metadata data)
    : d_(std::make_unique<quasar_image_metadata>(data)) {}
}  // namespace quasar
