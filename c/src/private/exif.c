#include <quasar/api/ffi/exif.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <quasar/api/ffi/crc16.h>
#include <private/extern/json.h>

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
  size_t const buffer_size
) {
  struct json_value_s* root = malloc(sizeof(struct json_object_s));
  char* cursor = buffer;
  size_t const written = snprintf(
    cursor,
    buffer_size,
    "{\n"
    "  \"nav\": {\n"
    "    \"coordinates\": [%.10f, %.10f],\n"
    "    \"velocity\": %.4f,\n"
    "    \"altitude\": %.4f,\n"
    "    \"azimuth\": %.4f\n"
    "  },\n"
    "  \"resolution\": {\n"
    "    \"dx\": %.6f,\n"
    "    \"dy\": %.6f\n"
    "  },\n"
    "  \"dimensions\": {\n"
    "    \"lx\": %.6f,\n"
    "    \"ly\": %.6f,\n"
    "    \"x0\": %.6f,\n"
    "    \"y0\": %.6f\n"
    "  },\n"
    "  \"drift_angle\": %.6f,\n"
    "  \"div\": %.6f,\n"
    "  \"mode\": %u,\n"
    "  \"fic\": %.6f,\n"
    "  \"time_offset\": %.6f,\n"
    "  \"time_duration\": %.6f,\n"
    "  \"image_type\": \"%s\"\n"
    "}\n",
    metadata->latitude,
    metadata->longitude,
    metadata->velocity,
    metadata->altitude,
    metadata->angle,
    metadata->dx,
    metadata->dy,
    metadata->lx,
    metadata->ly,
    metadata->x0,
    metadata->y0,
    metadata->drift_angle,
    metadata->divergence_angle,
    metadata->sar_mode,
    metadata->fic,
    metadata->time_offset,
    metadata->time_duration,
    quasar_image_kind_name(metadata->kind)
  );
  if(written >= buffer_size)
    buffer[buffer_size - 1] = '\0';
  free(root);
}

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

struct quasar_image_metadata
  quasar_image_metadata_from_json(char const* json, size_t const json_size) {
  struct quasar_image_metadata m = quasar_image_metadata_empty();

  struct json_value_s* root = json_parse(json, json_size);
  if(! root || root->type != json_type_object)
    return m;

  const struct json_object_s* obj = (struct json_object_s*)root->payload;
  const struct json_object_element_s* e = obj->start;
  while(e) {
    if(strcmp(e->name->string, "nav") == 0) {
      const struct json_object_element_s* nav = ((struct json_object_s*)e->value->payload)->start;
      while(nav) {
        if(strcmp(nav->name->string, "coordinates") == 0) {
          struct json_array_s* coord = nav->value->payload;
          m.latitude = atof(((struct json_string_s*)coord->start->value->payload)->string);
          m.longitude = atof(((struct json_string_s*)coord->start->next->value->payload)->string);
        } else if(strcmp(nav->name->string, "velocity") == 0) {
          m.velocity = atof(((struct json_string_s*)nav->value->payload)->string);
        } else if(strcmp(nav->name->string, "altitude") == 0) {
          m.altitude = atof(((struct json_string_s*)nav->value->payload)->string);
        } else if(strcmp(nav->name->string, "azimuth") == 0) {
          m.angle = atof(((struct json_string_s*)nav->value->payload)->string);
        }
        nav = nav->next;
      }
    } else if(strcmp(e->name->string, "resolution") == 0) {
      struct json_object_element_s* res = ((struct json_object_s*)e->value->payload)->start;
      while(res) {
        if(strcmp(res->name->string, "dx") == 0) {
          m.dx = atof(((struct json_string_s*)res->value->payload)->string);
        } else if(strcmp(res->name->string, "dy") == 0) {
          m.dy = atof(((struct json_string_s*)res->value->payload)->string);
        }
        res = res->next;
      }
    } else if(strcmp(e->name->string, "dimensions") == 0) {
      struct json_object_element_s* dim = ((struct json_object_s*)e->value->payload)->start;
      while(dim) {
        if(strcmp(dim->name->string, "lx") == 0)
          m.lx = atof(((struct json_string_s*)dim->value->payload)->string);
        else if(strcmp(dim->name->string, "ly") == 0)
          m.ly = atof(((struct json_string_s*)dim->value->payload)->string);
        else if(strcmp(dim->name->string, "x0") == 0)
          m.x0 = atof(((struct json_string_s*)dim->value->payload)->string);
        else if(strcmp(dim->name->string, "y0") == 0)
          m.y0 = atof(((struct json_string_s*)dim->value->payload)->string);
        dim = dim->next;
      }
    } else if(strcmp(e->name->string, "drift_angle") == 0)
      m.drift_angle = atof(((struct json_string_s*)e->value->payload)->string);
    else if(strcmp(e->name->string, "div") == 0)
      m.divergence_angle = atof(((struct json_string_s*)e->value->payload)->string);
    else if(strcmp(e->name->string, "mode") == 0)
      m.sar_mode = (uint8_t)atoi(((struct json_string_s*)e->value->payload)->string);
    else if(strcmp(e->name->string, "fic") == 0)
      m.fic = atof(((struct json_string_s*)e->value->payload)->string);
    else if(strcmp(e->name->string, "time_offset") == 0)
      m.time_offset = atof(((struct json_string_s*)e->value->payload)->string);
    else if(strcmp(e->name->string, "time_duration") == 0)
      m.time_duration = atof(((struct json_string_s*)e->value->payload)->string);
    else if(strcmp(e->name->string, "image_type") == 0)
      m.kind = image_kind_from_str(((struct json_string_s*)e->value->payload)->string);

    e = e->next;
  }

  free(root);
  return m;
}
