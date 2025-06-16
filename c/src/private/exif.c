#include <quasar/api/ffi/exif.h>

#include <stdlib.h>
#include <quasar/api/ffi/crc16.h>

static uint8_t image_kind_from_str(char const* type) {
  if(strcmp(type, "telescopic") == 0)
    return QUASAR_IMAGE_KIND_TELESCOPIC;
  if(strcmp(type, "strip") == 0)
    return QUASAR_IMAGE_KIND_STRIP;
  return QUASAR_IMAGE_KIND_UNDEFINED;
}

struct quasar_image_metadata quasar_image_metadata_empty() {
  struct quasar_image_metadata m;
  quasar_image_metadata_init(&m);
  return m;
}

void quasar_image_metadata_init(struct quasar_image_metadata* metadata) {
  metadata->latitude = 0.0;
  metadata->longitude = 0.0;
  metadata->dx = 0.0f;
  metadata->dy = 0.0f;
  metadata->x0 = 0.0f;
  metadata->y0 = 0.0f;
  metadata->angle = 0.0f;
  metadata->drift_angle = 0.0f;
  metadata->lx = 0.0f;
  metadata->ly = 0.0f;
  metadata->divergence_angle = 0.0f;
  metadata->velocity = 0.0f;
  metadata->altitude = 0.0f;
  metadata->fic = 0.0f;
  metadata->time_offset = 0.0f;
  metadata->time_duration = 0.0f;
  metadata->library_version[0] = 0;
  metadata->library_version[1] = 0;
  metadata->library_version[2] = 0;
  metadata->__reserved_1[0] = 0;
  metadata->__reserved_1[1] = 0;
  metadata->sar_mode = 0;
  metadata->kind = QUASAR_IMAGE_KIND_UNDEFINED;
  metadata->timestamp = 0;
  metadata->crc16 = 0;
}

uint16_t quasar_image_metadata_checksum(struct quasar_image_metadata const* metadata) {
  return quasar_crc16(
    (uint8_t const*)metadata,
    sizeof(struct quasar_image_metadata) - sizeof(uint16_t)
  );
}

struct quasar_image_metadata
  quasar_image_metadata_from_exif(uint8_t const* exif_data, size_t const exif_data_size) {
  if(! exif_data
     || exif_data_size
          < (sizeof(struct quasar_image_metadata) + QUASAR_IMAGE_METADATA_EXIF_HEADER_OFFSET))
    return quasar_image_metadata_empty();

  size_t const exif_offset = QUASAR_IMAGE_METADATA_EXIF_HEADER_OFFSET;
  if((exif_offset + sizeof(struct quasar_image_metadata_exif_header)) > exif_data_size)
    return quasar_image_metadata_empty();

  struct quasar_image_metadata_exif_header header;
  memcpy(&header, exif_data + exif_offset, sizeof(header));
  header.marker = quasar_byteswap16(header.marker);

  if(header.marker != QUASAR_IMAGE_METADATA_EXIF_HEADER_MARKER)
    return quasar_image_metadata_empty();

  size_t const metadata_offset = exif_offset + sizeof(header);
  if((metadata_offset + sizeof(struct quasar_image_metadata)) > exif_data_size)
    return quasar_image_metadata_empty();

  struct quasar_image_metadata result;
  memcpy(&result, exif_data + metadata_offset, sizeof(result));

  // if legacy
  if(result.library_version[0] * 100'000 + result.library_version[1] * 1'000
       + result.library_version[2]
     < 106'000) {
    result.velocity /= 3.6f;
  }

  return result;
}
