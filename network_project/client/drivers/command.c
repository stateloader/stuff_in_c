/*------------------------------------------------------------------------------------------------------------Command Main
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  MQUIT  |    -    |    -    |    -    |    -    |     -    |   MDVCE   |   MMESG   |
                                    --------------------------------------------------------------------------------------
                                    |                                     MIN MENUES                                     |
------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------Command Late
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  LBACK  |    -    |    -    |    -    |    -    |   LOPT2  |   LOPT1   |   LOPT0   |
                                    --------------------------------------------------------------------------------------
                                    |                                     LATE MENUES                                    |
------------------------------------------------------------------------------------------------------------------------*/

#include "scanner.h"
#include "cstring.h"
#include "command.h"

static const uint8_t MMESG = 0x00;
static const uint8_t MDVCE = 0x01;
static const uint8_t MQUIT = 0x07;

static const uint8_t LOPT0 = 0x00;
static const uint8_t LOPT1 = 0x01;
static const uint8_t LOPT2 = 0x02;
static const uint8_t LOPT3 = 0x03;
static const uint8_t LBACK = 0x07;

typedef int8_t (*cmnd_func)(cmnd_t *cmnd);

typedef struct CmndItem {
  const char *cmnd;
  const uint8_t byte;
  cmnd_func func;
} cmnd_item;

static void cmnd_scan(cmnd_t *cmnd) {
;
}

static void cmnd_main(cmnd_t *cmnd) {
  Render_Header("MAIN", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
  cmnd->status = 0;
}

static void cmnd_mesg(cmnd_t *cmnd) {
  Render_Header("MESSAGE", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");  
}

static void cmnd_dvce(cmnd_t *cmnd) {
  Render_Header("DEVICE", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");

}

static void cmnd_quit(cmnd_t *cmnd) {
  Render_Header("QUIT", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
}

static cmnd_item main_items[] = {
  {"-message", MMESG, cmnd_mesg},
  {"-device", MDVCE, cmnd_dvce},
  {"-quit", MQUIT, cmnd_quit},
};

int8_t command_driver(cmnd_t *cmnd) {
  System_Message("Inside command driver");

  while (cmnd->status == 1)
    cmnd_main(cmnd);
  return SUCC;
}