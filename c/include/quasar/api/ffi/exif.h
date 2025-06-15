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
  uint8_t __reserved_2[8];      ///< Reserved for future use.
  uint16_t crc16;               ///< CRC16 checksum of the metadata.
};

#pragma pack(pop)

static_assert(
  sizeof(struct quasar_image_metadata) == 92,
  "quasar_image_metadata must be 92 bytes long"
);
static_assert(
  alignof(struct quasar_image_metadata) == 1,
  "quasar_image_metadata must be aligned to 1 byte (pragma pack(1))"
);

QUASAR_C_API void quasar_image_metadata_init(struct quasar_image_metadata* metadata);
QUASAR_C_API struct quasar_image_metadata quasar_image_metadata_empty();
QUASAR_C_API uint16_t quasar_image_metadata_checksum(struct quasar_image_metadata const* metadata);
QUASAR_C_API void quasar_image_metadata_to_json(
  struct quasar_image_metadata const* metadata,
  char* buffer,
  size_t buffer_size
);
QUASAR_C_API struct quasar_image_metadata
  quasar_image_metadata_from_json(char const* json, size_t json_size);
QUASAR_C_API struct quasar_image_metadata
  quasar_image_metadata_from_exif(uint8_t const* exif_data, size_t exif_data_size);
// QUASAR_C_API void quasar_image_metadata_to_exif(
//   struct quasar_image_metadata const* metadata,
//   uint8_t* exif_data,
//   size_t exif_data_size
// );

static size_t const QUASAR_IMAGE_METADATA_EXIF_HEADER_OFFSET = 20;
static uint16_t const QUASAR_IMAGE_METADATA_EXIF_HEADER_MARKER = 0xFFE1;

struct quasar_image_metadata_exif_header {
  uint16_t marker;
  uint16_t length;
};

QUASAR_C_API_END
