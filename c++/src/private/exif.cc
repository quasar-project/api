#include <quasar/api/exif.h>

#include <vector>
#include <fmt/chrono.h>
#include <quasar/api/ffi/exif.h>

#ifdef _MSC_VER
#  include <ciso646>
#endif

namespace quasar {
  ImageMetadata::ImageMetadata()
    : d_(std::make_unique<quasar_image_metadata>()) {
    ::quasar_image_metadata_init(d_.get());
  }

  ImageMetadata::ImageMetadata(ImageMetadata const& other)
    : d_(std::make_unique<quasar_image_metadata>(*other.d_)) {}

  ImageMetadata& ImageMetadata::operator=(ImageMetadata const& other) {
    *this = ImageMetadata(*other.d_);
    return *this;
  }

  ImageMetadata::ImageMetadata(ImageMetadata&& other) noexcept
    : d_(std::move(other.d_)) {}

  ImageMetadata& ImageMetadata::operator=(ImageMetadata&& other) noexcept {
    this->d_ = std::move(other.d_);
    return *this;
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

  std::chrono::system_clock::time_point ImageMetadata::timestamp() const noexcept {
    return std::chrono::system_clock::from_time_t(d_->timestamp);
  }

  void ImageMetadata::set_timestamp(std::chrono::system_clock::time_point timestamp) noexcept {
    d_->timestamp = std::chrono::system_clock::to_time_t(timestamp);
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

  nlohmann::json ImageMetadata::to_json() const {
    auto j = nlohmann::json::object();
    j["meta"] = nlohmann::json::object();
    j["meta"]["timestamp"] = nlohmann::json::object();
    j["meta"]["timestamp"]["unix"] = this->timestamp().time_since_epoch().count();
    j["meta"]["timestamp"]["human"] = fmt::format("{:%Y-%m-%d %H:%M:%S}", this->timestamp());
    j["meta"]["library_version"] = this->library_version();
    j["meta"]["sar_mode"] = this->sar_mode();
    j["image_kind"] = this->kind();
    j["nav"] = nlohmann::json::object();
    j["nav"]["coordinates"] = {this->latitude(), this->longitude()};
    j["nav"]["velocity"] = this->velocity();
    j["nav"]["altitude"] = this->altitude();
    j["image"] = nlohmann::json::object();
    j["image"]["resolution"] = {
      {"dx", this->dx()},
      {"dy", this->dy()}
    };
    j["image"]["dimensions"] = {
      {"lx", this->width()      },
      {"ly", this->height()     },
      {"x0", this->near_edge()  },
      {"y0", this->frame_shift()}
    };
    j["image"]["angle"] = this->angle();
    j["image"]["drift_angle"] = this->drift_angle();
    if(this->kind() == ImageKind::Telescopic)
      j["image"]["div"] = this->divergence_angle();
    else
      j["image"]["div"] = nullptr;
    j["image"]["fic"] = this->frequency_interpolation_coefficient();
    j["image"]["time_offset"] = this->time_offset().count();
    j["image"]["time_duration"] = this->time_duration().count();
    return j;
  }

  std::string ImageMetadata::to_json_string(std::size_t const indent) const {
    return this->to_json().dump(static_cast<int>(indent));
  }

  ImageMetadata ImageMetadata::from_json(nlohmann::json const& json) {
    auto const is_legacy = not json.contains("meta") or not json["meta"].contains("library_version")
                        or not json["meta"]["library_version"].is_array()
                        or json["meta"]["library_version"].size() != 3;
    if(is_legacy)
      return ImageMetadata::from_legacy_json(json);
    auto m = ImageMetadata();
    m.set_latitude(json["nav"]["coordinates"][0].get<double>());
    m.set_longitude(json["nav"]["coordinates"][1].get<double>());
    m.set_velocity(json["nav"]["velocity"].get<float>());
    m.set_altitude(json["nav"]["altitude"].get<float>());
    m.set_angle(json["image"]["angle"].get<float>());
    m.set_dx(json["image"]["resolution"]["dx"].get<float>());
    m.set_dy(json["image"]["resolution"]["dy"].get<float>());
    m.set_width(json["image"]["dimensions"]["lx"].get<float>());
    m.set_height(json["image"]["dimensions"]["ly"].get<float>());
    m.set_near_edge(json["image"]["dimensions"]["x0"].get<float>());
    m.set_frame_shift(json["image"]["dimensions"]["y0"].get<float>());
    auto const drift_angle = json["image"]["drift_angle"];
    m.set_drift_angle(drift_angle.is_null() ? 0.f : drift_angle.get<float>());
    if(json["image"].contains("div") and not json["image"]["div"].is_null())
      m.set_divergence_angle(json["image"]["div"].get<float>());
    else
      m.set_divergence_angle(0.f);
    m.set_frequency_interpolation_coefficient(json["image"]["fic"].get<float>());
    m.set_time_offset(std::chrono::duration<double>(json["image"]["time_offset"].get<double>()));
    m.set_time_duration(
      std::chrono::duration<double>(json["image"]["time_duration"].get<double>())
    );
    m.set_kind(json["image_kind"].get<ImageKind>());
    m.set_library_version(
      {json["meta"]["library_version"][0].get<std::uint16_t>(),
       json["meta"]["library_version"][1].get<std::uint16_t>(),
       json["meta"]["library_version"][2].get<std::uint16_t>()}
    );
    m.set_sar_mode(json["meta"]["sar_mode"].get<std::uint8_t>());
    m.set_timestamp(
      std::chrono::system_clock::from_time_t(json["meta"]["timestamp"]["unix"].get<std::time_t>())
    );
    return m;
  }

  ImageMetadata ImageMetadata::from_json_string(std::string_view const json) {
    return ImageMetadata::from_json(nlohmann::json::parse(json));
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

  ImageMetadata ImageMetadata::from_legacy_json(nlohmann::json const& json) {
    auto const& nav = json["nav"];
    auto const& resolution = json["resolution"];
    auto const& dimensions = json["dimensions"];
    auto m = ImageMetadata();
    m.set_latitude(nav["coordinates"][0]);
    m.set_longitude(nav["coordinates"][1]);
    m.set_velocity(nav["velocity"].get<float>() / 3.6f);  // Convert from km/h to m/s
    m.set_altitude(nav["altitude"]);
    m.set_angle(nav["azimuth"]);
    m.set_dx(resolution["dx"]);
    m.set_dy(resolution["dy"]);
    m.set_width(dimensions["lx"]);
    m.set_height(dimensions["ly"]);
    m.set_near_edge(dimensions["x0"]);
    m.set_frame_shift(dimensions["y0"]);
    auto const& drift_angle = json["drift_angle"];
    m.set_drift_angle(drift_angle.is_null() ? 0.f : static_cast<float>(drift_angle));
    m.set_divergence_angle(json["div"]);
    m.set_sar_mode(json["mode"]);
    m.set_frequency_interpolation_coefficient(json["fic"]);
    m.set_time_offset(std::chrono::duration<double>(json["time_offset"]));
    m.set_time_duration(std::chrono::duration<double>(json["time_duration"]));
    m.set_kind(json["image_type"] == "telescopic" ? ImageKind::Telescopic : ImageKind::Strip);
    m.set_library_version({1, 6, 0});
    return m;
  }
}  // namespace quasar
