/*------------------------------------------------------------------------------------------------------------Command Task
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  MMENU  |    -    |    -    |    -    |    -    |     -    |   TDVCE   |   TMESG   |
                                    --------------------------------------------------------------------------------------
                                    |                                     MODE MENUES                                    |
------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------Command Exec
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |    -    |    -    |    -    |    -    |    -    |   LOPT2  |   LOPT1   |   LOPT0   |
                                    --------------------------------------------------------------------------------------
                                    |                                     LATE MENUES                                    |
------------------------------------------------------------------------------------------------------------------------*/

#include "scanner.h"
#include "cstring.h"
#include "command.h"

static const uint8_t TMESG = 0x00;
static const uint8_t TDVCE = 0x01;
static const uint8_t MMENU = 0x07;

static const uint8_t EOPT0 = 0x00;
static const uint8_t EOPT1 = 0x01;
static const uint8_t EOPT2 = 0x02;

typedef void (*cmnd_func)(cmnd_t *cmnd);

typedef struct CmndItem {
  const char *cmnd;
  const uint8_t byte;
  cmnd_func func;
} cmnd_item;

static void command_quit(cmnd_t *cmnd) {
  cmnd->task_byte &= ~(1 << MMENU);
}

static void request_canonical_mesg(cmnd_t *cmnd) {

  cmnd->rqst_byte |= (1 << 0);

  if (cmnd->exec_byte & (1 << EOPT0))
    cmnd->rqst_byte |= (0 << 7);
  else
    cmnd->rqst_byte |= (1 << 7);

  command_quit(cmnd);
}

static void request_canonical_dvce(cmnd_t *cmnd) {
  cmnd->task_byte &= ~(1 << MMENU);

  cmnd->exec_byte |= (1 << 7);

  if (cmnd->exec_byte & (1 << EOPT0))
    cmnd->rqst_byte |= (1 << 4);
  else if (cmnd->exec_byte & (1 << EOPT1))
    cmnd->rqst_byte |= (1 << 5);
  else
    cmnd->rqst_byte |= (1 << 6);

  command_quit(cmnd);
}

static void command_optn(cmnd_item *items, size_t size_array) {
  for (size_t i = 0; i < size_array; i++)
    printf("\t\t%s\n", items[i].cmnd);
}

static cmnd_item mesg_items[] = {
  {"-send", EOPT0, request_canonical_mesg},
  {"-read", EOPT1, request_canonical_mesg},
};

static cmnd_item dvce_items[] = {
  {"-red", EOPT0, request_canonical_dvce},
  {"-blue", EOPT1, request_canonical_dvce},
  {"-green", EOPT2, request_canonical_dvce},
};

static void command_dvce(cmnd_t *cmnd) {
  Render_Header("DEVICE", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
  command_optn(dvce_items, ARRAY_SIZE(dvce_items));

  cmnd->size_cmnd = scan_driver(cmnd->command, SBUFF, "select");

  for (size_t i = 0; i < ARRAY_SIZE(dvce_items); i++) {
    if (string_comp(cmnd->command, dvce_items[i].cmnd, cmnd->size_cmnd)) {
      cmnd->exec_byte |= (1 << dvce_items[i].byte);
      dvce_items[i].func(cmnd);
    }
  }
}

static void command_mesg(cmnd_t *cmnd) {
  Render_Header("MESSAGE", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");  
  command_optn(mesg_items, ARRAY_SIZE(mesg_items));

  cmnd->size_cmnd = scan_driver(cmnd->command, SBUFF, "select");

  for (size_t i = 0; i < ARRAY_SIZE(mesg_items); i++) {
    if (string_comp(cmnd->command, mesg_items[i].cmnd, cmnd->size_cmnd)) {
      cmnd->exec_byte |= (1 << mesg_items[i].byte);
      mesg_items[i].func(cmnd);
    }
  }
}

static cmnd_item main_items[] = {
  {"-message", TMESG, command_mesg},
  {"-device", TDVCE, command_dvce},
  {"-leave", MMENU, command_quit},
};

static void command_main(cmnd_t *cmnd) {
  Render_Header("MAIN MENU", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
  command_optn(main_items, ARRAY_SIZE(main_items));

  cmnd->size_cmnd = scan_driver(cmnd->command, SBUFF, "select");

  for (size_t i = 0; i < ARRAY_SIZE(main_items); i++) {
    if (string_comp(cmnd->command, main_items[i].cmnd, cmnd->size_cmnd)) {
      cmnd->task_byte |= (1 << main_items[i].byte);
      main_items[i].func(cmnd);
    }
  }
}

int8_t command_driver(cmnd_t *cmnd) {
  System_Message("Inside command driver");

  cmnd->task_byte |= (1 << MMENU);

  while (cmnd->task_byte & (1 << MMENU))
    command_main(cmnd);

  return command_driver_check(cmnd);
}