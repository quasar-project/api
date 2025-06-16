#pragma once

#include <stdalign.h>
#include <quasar/api/ffi/detail/definitions.h>
#include <quasar/api/ffi/enums.h>

QUASAR_C_API_BEGIN

#pragma pack(push, 1)

/**
 * @brief EXIF image metadata structure.
 */
struct quasar_image_metadata {
  double latitude;              ///< Latitude in degrees (WGS84).
  double longitude;             ///< Longitude in degrees (WGS84).
  float dx;                     ///< Pixel size in the X direction (in meters per pixel).
  float dy;                     ///< Pixel size in the Y direction (in meters per pixel).
  float x0;                     ///< Near edge offset in meters.
  float y0;                     ///< Frame shift in meters. Currently unused.
  float angle;                  ///< Rotation angle in radians relative to the anchor point.
  float drift_angle;            ///< Drift angle in radians relative to the anchor point.
  float lx;                     ///< Length of the frame in the X direction (in meters).
  float ly;                     ///< Length of the frame in the Y direction (in meters).
  float divergence_angle;       ///< Divergence angle in radians. Only used for telescopic images.
  float velocity;               ///< Velocity of the capture platform in meters per second.
  float altitude;               ///< Altitude of the capture platform in meters above sea level.
  float fic;                    ///< Frequency interpolation coefficient.
  float time_offset;            ///< Capture time offset in seconds.
  float time_duration;          ///< Capture time duration in seconds.
  uint16_t library_version[3];  ///< Library version (major, minor, patch).
  uint8_t __reserved_1[2];      ///< Reserved for future use.
  uint8_t sar_mode;             ///< SAR mode used for the image.
  uint8_t kind;                 ///< Type of the image (telescopic or strip).
  uint64_t timestamp;           ///< Unix timestamp of the image capture.
  uint16_t crc16;               ///< CRC16 checksum of the metadata.
};

#pragma pack(pop)

#ifdef _MSC_VER
static_assert(
  sizeof(struct quasar_image_metadata) == 92,
  "quasar_image_metadata must be 92 bytes long"
);
static_assert(
  alignof(struct quasar_image_metadata) == 1,
  "quasar_image_metadata must be aligned to 1 byte (pragma pack(1))"
);
#endif

/**
 * @brief Checks if the library version is greater, equal or less than the required version.
 * @param major rhs major version
 * @param minor rhs minor version
 * @param patch rhs patch version
 * @param required_major lhs major version
 * @param required_minor lhs minor version
 * @param required_patch lhs patch version
 * @return 0 if the versions are equal, 1 if the library version is greater than the required
 * version, -1 if the library version is less than the required version
 */
QUASAR_C_API int quasar_version_check(
  uint16_t major,
  uint16_t minor,
  uint16_t patch,
  uint16_t required_major,
  uint16_t required_minor,
  uint16_t required_patch
);

QUASAR_C_API void quasar_image_metadata_init(struct quasar_image_metadata* metadata);

QUASAR_C_API struct quasar_image_metadata quasar_image_metadata_empty();

QUASAR_C_API uint16_t quasar_image_metadata_checksum(struct quasar_image_metadata const* metadata);

QUASAR_C_API struct quasar_image_metadata
  quasar_image_metadata_from_exif(uint8_t const* exif_data, size_t exif_data_size, int* error);

static size_t const QUASAR_IMAGE_METADATA_EXIF_HEADER_OFFSET = 20;
static uint16_t const QUASAR_IMAGE_METADATA_EXIF_HEADER_MARKER = 0xFFE1;

struct quasar_image_metadata_exif_header {
  uint16_t marker;
  uint16_t length;
};

QUASAR_C_API_END
