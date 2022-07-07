#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "configs.h"

typedef struct Controller {
  uint8_t state;
  uint16_t error;
  uint8_t *protocol;
  int32_t sock_desc;
  size_t datm;
  char datetime[TBUFF];
  size_t size_user;
  size_t size_pass;
  char username[SBUFF];
  char password[SBUFF];
  size_t size_reqt;
  size_t size_recv;
  char request[SBUFF];
  char receive[RBUFF];
} cont_t;

void control_driver(cont_t *controller);

#endif
/*

static wise_item cont_item[] = {
  {"cont state", "ALIVE", ALIVE},
  {"cont state", "CONNF", CONNF},
  {"cont state", "RQSTF", REQTF},
  {"cont state", "RECVS", RECVF},
  {"cont state", "FATAL", FATAL},
};
*/

/*
  char string1[SBUFF];
  char string2[SBUFF]; //= {'\0'};
  char samling[SBUFF]; //= {'\0'};

  size_t str1 = scan_driver(string1, "string1", SBUFF);
  size_t str2 = scan_driver(string2, "string2", SBUFF);

  //printf("string 1 %s\n", string1);
  //printf("string 2 %s\n", string2);

  print_string_and_size(string1, str1);
  print_string_and_size(string2, str2);

  //size_t ccat = string_ccat(samling, string1, SBUFF);
*/

/*
  char string1[SBUFF];
  char string2[SBUFF]; //= {'\0'};
  char samling[SBUFF]; //= {'\0'};

  size_t str1 = scan_driver(string1, "string1", SBUFF);
  size_t str2 = scan_driver(string2, "string2", SBUFF);

  //printf("string 1 %s\n", string1);
  //printf("string 2 %s\n", string2);

  print_string_and_size(string1, str1);
  print_string_and_size(string2, str2);

  //size_t ccat = string_ccat(samling, string1, SBUFF);
    while (control->state & (0 << CONNF));
  while (control->state & (0 << CMNDF));

  while (control->state & (0 << REQTF));
void control_driver(cont_t *control) {
*/
  
