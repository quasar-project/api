#include <quasar/api/exif.h>

#include <quasar/api/crc16.h>

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
  metadata->__reserved_2[0] = 0;
  metadata->__reserved_2[1] = 0;
  metadata->__reserved_2[2] = 0;
  metadata->__reserved_2[3] = 0;
  metadata->__reserved_2[4] = 0;
  metadata->__reserved_2[5] = 0;
  metadata->__reserved_2[6] = 0;
  metadata->__reserved_2[7] = 0;
  metadata->crc16 = 0;
}

uint16_t quasar_image_metadata_checksum(struct quasar_image_metadata const* metadata) {
  return quasar_crc16(
    (uint8_t const*)metadata,
    sizeof(struct quasar_image_metadata) - sizeof(uint16_t)
  );
}

void quasar_image_metadata_to_json(
  struct quasar_image_metadata const* metadata,
  char* buffer,
  size_t buffer_size
) {}

struct quasar_image_metadata
  quasar_image_metadata_from_exif(uint8_t const* exif_data, size_t exif_data_size) {
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

  return result;
}

struct quasar_image_metadata quasar_image_metadata_from_json(char const* json, size_t json_size) {
  return quasar_image_metadata_empty();
}
