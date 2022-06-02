#ifndef VIEW_H_
#define VIEW_H_

#include "client.h"

#define ROWS 8
#define COLS 16

typedef struct View {
  char **main_menu;
  char **resp_menu;
  char **reqt_menu;
} view_t;

view_t views_create();
void view_driver(cent_t *client);

#endif
