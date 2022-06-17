#ifndef DEVICE_H_
#define DEVICE_H_

#include <stdint.h>
#include "cconfig.h"
#include "client.h"

int8_t device_driver(client_t *client, int8_t choice);

#endif
