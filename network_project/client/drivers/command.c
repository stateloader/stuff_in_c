/*------------------------------------------------------------------------------------------------------------Command Main
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  MMENU  |    -    |    -    |    -    |    -    |     -    |   MDVCE   |   MMESG   |
                                    --------------------------------------------------------------------------------------
                                    |                                     MIN MENUES                                     |
------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------Command Late
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  LFAIL  |    -    |    -    |    -    |    -    |   LOPT2  |   LOPT1   |   LOPT0   |
                                    --------------------------------------------------------------------------------------
                                    |                                     LATE MENUES                                    |
------------------------------------------------------------------------------------------------------------------------*/

#include "scanner.h"
#include "cstring.h"
#include "command.h"

static const uint8_t MMESG = 0x00;
static const uint8_t MDVCE = 0x01;
static const uint8_t MMENU = 0x07;

static const uint8_t LOPT0 = 0x00;
static const uint8_t LOPT1 = 0x01;
static const uint8_t LOPT2 = 0x02;

typedef void (*cmnd_func)(cmnd_t *cmnd);

typedef struct CmndItem {
  const char *cmnd;
  const uint8_t byte;
  cmnd_func func;
} cmnd_item;

static void cmnd_done(cmnd_t *cmnd) {
  cmnd->main_byte &= ~(1 << MMENU);
}

static void cmnd_optn(cmnd_item *items, size_t size_array) {
  for (size_t i = 0; i < size_array; i++)
    printf("\t\t%s\n", items[i].cmnd);
}

static cmnd_item mesg_items[] = {
  {"-send", LOPT0, cmnd_done},
  {"-read", LOPT1, cmnd_done},
};

static cmnd_item dvce_items[] = {
  {"-red", LOPT0, cmnd_done},
  {"-blue", LOPT1, cmnd_done},
  {"-green", LOPT2, cmnd_done},
};

static void cmnd_dvce(cmnd_t *cmnd) {
  Render_Header("DEVICE", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
  cmnd_optn(dvce_items, ARRAY_SIZE(dvce_items));

  cmnd->size_cmnd = scan_driver(cmnd->command, SBUFF, "select");

  for (size_t i = 0; i < ARRAY_SIZE(dvce_items); i++) {
    if (string_comp(cmnd->command, dvce_items[i].cmnd, cmnd->size_cmnd)) {
      cmnd->late_byte |= (1 << dvce_items[i].byte);
      dvce_items[i].func(cmnd);
    }
  }
}

static void cmnd_mesg(cmnd_t *cmnd) {
  Render_Header("MESSAGE", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");  
  cmnd_optn(mesg_items, ARRAY_SIZE(mesg_items));

  cmnd->size_cmnd = scan_driver(cmnd->command, SBUFF, "select");

  for (size_t i = 0; i < ARRAY_SIZE(mesg_items); i++) {
    if (string_comp(cmnd->command, mesg_items[i].cmnd, cmnd->size_cmnd)) {
      cmnd->late_byte |= (1 << mesg_items[i].byte);
      mesg_items[i].func(cmnd);
    }
  }
}

static cmnd_item main_items[] = {
  {"-message", MMESG, cmnd_mesg},
  {"-device", MDVCE, cmnd_dvce},
  {"-quit", MMENU, cmnd_done},
};

static void cmnd_main(cmnd_t *cmnd) {
  Render_Header("MAIN", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
  cmnd_optn(main_items, ARRAY_SIZE(main_items));

  cmnd->size_cmnd = scan_driver(cmnd->command, SBUFF, "select");

  for (size_t i = 0; i < ARRAY_SIZE(main_items); i++) {
    if (string_comp(cmnd->command, main_items[i].cmnd, cmnd->size_cmnd)) {
      cmnd->main_byte |= (1 << main_items[i].byte);
      main_items[i].func(cmnd);
    }
  }
}

int8_t command_driver(cmnd_t *cmnd) {
  System_Message("Inside command driver");

  cmnd->main_byte |= (1 << MMENU);

  while (cmnd->main_byte & (1 << MMENU))
    cmnd_main(cmnd);
  return SUCC;
}