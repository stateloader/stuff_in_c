#include "view.h"

/*-------------------------------------------------------------------------------------
                                                                               MEMORY
-------------------------------------------------------------------------------------*/

static void view_memory_alloc(view_t *view) {

  view->main_menu = (char**) malloc(ROWS * sizeof(char *));
  view->resp_menu = (char**) malloc(ROWS * sizeof(char *));
  view->reqt_menu = (char**) malloc(ROWS * sizeof(char *));

  for (size_t i = 0; i < ROWS; i++) {
    view->main_menu[i] = (char *) malloc(COLS * sizeof(char));
    view->resp_menu[i] = (char *) malloc(ROWS * sizeof(char));
    view->reqt_menu[i] = (char *) malloc(ROWS * sizeof(char));
  }
}

static void view_memory_free(view_t *view) {

  for (size_t i = 0; i < ROWS; i++) {
    free(view->main_menu[i]);
    free(view->resp_menu[i]);
    free(view->reqt_menu[i]);
  }
  free(view->main_menu);
  free(view->resp_menu);
  free(view->reqt_menu);
}

/*-------------------------------------------------------------------------------------
                                                                               RENDER
-------------------------------------------------------------------------------------*/

static void render_main_menu(char **view) {
 ;
}

/*-------------------------------------------------------------------------------------
                                                                                 VIEW
-------------------------------------------------------------------------------------*/

view_t views_create() {
  view_t views;
  view_memory_alloc(&views);
  view_memory_free(&views);
}

static void view_main_menu(cent_t *client) {
  printf("Here's main menu.\n");
}

static void view_resp_menu(cent_t *client) {
  printf("Here's response.\n");
}

static void view_reqt_menu(cent_t *client) {
  printf("Here's request.n\n");
}

typedef void (*view_func)(cent_t *client);

typedef struct {
  view_func func;
} view_item;

static view_item view_items[] = {
  {view_main_menu}, {view_resp_menu}, {view_reqt_menu}
};

void view_driver(cent_t *client) {
  view_items[client->view].func(client);
}


