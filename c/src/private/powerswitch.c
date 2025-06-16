#include <quasar/api/ffi/powerswitch.h>

void quasar_powerswitch_request_init(struct quasar_powerswitch_request* request) {
  request->marker = QUASAR_POWERSWITCH_REQUEST_MARKER;
  request->channel = QUASAR_POWERSWITCH_REQUEST_DUMMY_CHANNEL;
  request->response_port = 0;
  request->checksum = 0;
}

void quasar_powerswitch_response_init(struct quasar_powerswitch_response* response) {
  response->marker = 0;
  response->channel = 0;
  response->enabled = 0;
  response->voltage = 0;
}
