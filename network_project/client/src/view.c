#include "view.h"

// se över hela logiken.

/*-------------------------------------------------------------------------------------
                                                                               MEMORY
-------------------------------------------------------------------------------------*/

static void view_memory_alloc(view_t *view) {

  view->curr_view = (char**) malloc(ROWS * sizeof(char *));
  for (size_t i = 0; i < ROWS; i++)
    view->curr_view[i] = (char *) malloc(COLS * sizeof(char));
}

static void view_memory_free(view_t *view) {

  for (size_t i = 0; i < ROWS; i++)
    free(view->curr_view[i]);
  free(view->curr_view);
}

void memory_driver(uint8_t controller, view_t *view) {

  if (controller) view_memory_alloc(view);
  else view_memory_free(view);
}

/*-------------------------------------------------------------------------------------
                                                                               RENDER
-------------------------------------------------------------------------------------*/

static void clear_old_view(view_t *view) {

  for (size_t i = 0; i < ROWS; i++) {
    for (size_t j = 0; i < COLS; j++) {
      view->curr_view[i][j] = '\0';
    }
  }
}

static void draw_new_view(uint8_t controller, view_t *view) {

  for (size_t i = 0; i < ROWS; i++) {
    for (size_t j = 0; i < COLS; j++) {
      if (controller == WMENU)
        view->curr_view[i][j] = '#';
      else if (controller == WRQST)
        view->curr_view[i][j] = 'o';
      else
        view->curr_view[i][j] = '%';
    }
  }
}

void render_view(cent_t *client, view_t *view) {


}

/*-------------------------------------------------------------------------------------
                                                                                 VIEW
-------------------------------------------------------------------------------------*/
/*
static void view_main_menu(cent_t *client) {
  printf("Here's main menu.\n");
}

static void view_resp_menu(cent_t *client) {
  printf("Here's response.\n");
}

static void view_rqst_menu(cent_t *client) {
  printf("Here's request.n\n");
}

typedef void (*view_func)(cent_t *client);

typedef struct {
  view_func func;
} view_item;

static view_item view_items[] = {
  {view_main_menu}, {view_resp_menu}, {view_rqst_menu}
};

void view_driver(cent_t *client) {
  view_items[client->view].func(client);
}
*/
