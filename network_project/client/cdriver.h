#ifndef CDRIVER_H_
#define CDRIVER_H_

#include "system/configs.h"
#include "connect/connection.h"

typedef struct ClientDriver {
  uint8_t state;
  uint16_t error;
  uint8_t protocol[3];
  clnt_t client;
} dver_t;

void client_driver(dver_t *driver);

#endif


 // uint8_t *protocol;
 // int32_t sock_desc;
  //size_t datm;
  //char datetime[TBUFF];
 // size_t size_user;
  //size_t size_pass;
 // char username[SBUFF];
 // char password[SBUFF];
  //size_t size_reqt;
  //size_t size_recv;
  //char request[SBUFF];
  //char receive[RBUFF];