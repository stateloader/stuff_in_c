#ifndef BROSWER_H_
#define BROWSER_H_

#include "controller.h"
#include "client.h"

#define BMAIN 0
#define BMESG 1
#define BDVCE 2
#define BDLED 3
#define BINIT 4
#define BEXIT 5

int8_t browse_driver(client_t *client);

#endif
