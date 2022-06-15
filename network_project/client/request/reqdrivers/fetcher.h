#ifndef FETCHER_H_
#define FETCHER_H_

#include <stdint.h>
#include "utils/cconfig.h"
#include "../client.h"

int8_t fetch_driver(client_t *client, int8_t choice);

#endif
