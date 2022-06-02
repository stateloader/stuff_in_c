#ifndef VIEW_H_
#define VIEW_H_

#include "client.h"

#define ROWS 8
#define COLS 16

typedef struct View {
  char **curr_view;
} view_t;

void memory_driver(uint8_t controller, view_t *view);
void render_view(cent_t *client, view_t *view);

#endif
