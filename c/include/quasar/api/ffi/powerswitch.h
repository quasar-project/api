#pragma once

#include <quasar/api/ffi/detail/definitions.h>

QUASAR_C_API_BEGIN

static uint32_t const QUASAR_POWERSWITCH_REQUEST_MARKER = 0xAAAAAAAA;
static uint16_t const QUASAR_POWERSWITCH_REQUEST_DUMMY_CHANNEL = 0x270F;
static uint32_t const QUASAR_POWERSWITCH_RESPONSE_MARKER = 0xBBBBBBBB;

#pragma pack(push, 1)

struct quasar_powerswitch_request {
  uint32_t marker;
  uint16_t channel;
  uint16_t response_port;
  uint16_t checksum;
};

#pragma pack(pop)

QUASAR_C_API void quasar_powerswitch_request_init(struct quasar_powerswitch_request* request);

#pragma pack(push, 1)

struct quasar_powerswitch_response {
  uint16_t marker;
  uint8_t channel;
  uint8_t enabled;
  uint32_t voltage;  ///< Voltage in millivolts.
  uint32_t current;  ///< Current in milliamperes.
};

#pragma pack(pop)

QUASAR_C_API void quasar_powerswitch_response_init(struct quasar_powerswitch_response* response);

QUASAR_C_API_END
