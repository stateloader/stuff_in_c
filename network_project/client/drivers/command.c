#include "scanner.h"
#include "cstring.h"
#include "command.h"

static const uint8_t MMESG = 0x01;
static const uint8_t MDVCE = 0x02;
static const uint8_t MMENU = 0x07;

static const uint8_t LOPT0 = 0x00;
static const uint8_t LOPT1 = 0x01;
static const uint8_t LOPT2 = 0x02;
static const uint8_t LOPT3 = 0x03;
static const uint8_t LBACK = 0x03;


/*------------------------------------------------------------------------------------------------------------Command Main
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  MMENU  |    -    |    -    |    -    |    -    |     -    |   DVICE   |   MMESG   |
                                    --------------------------------------------------------------------------------------
                                    |                                     MIN MENUES                                     |
------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------Command Late
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  LBACK  |    -    |    -    |    -    |    -    |   LOPT2  |   LOPT1   |   LOPT0   |
                                    --------------------------------------------------------------------------------------
                                    |                                     LATE MENUES                                    |
------------------------------------------------------------------------------------------------------------------------*/

static cmnd_item main_items[] = {
  {"-device", MDVCE}, {"-message", MMESG}, {"-quit", MMENU}};

static cmnd_item mesg_items[] = {
  {"-send", LOPT0}, {"-read", LOPT1}, {"-back", LBACK}};

static cmnd_item dvce_items[] = {
  {"-init red", LOPT0}, {"-init blue", LOPT1}, {"-init green", LOPT2}, {"-back", LBACK}};


static void command_scanner(cmnd_t *cmnd, cmnd_item *items, size_t arrsize) {
    
  for (size_t i = 0; i < arrsize; i++)
    printf("\t\t%s\n", items[i].cmnd);

  int8_t match = 0;
  while (cmnd->main_byte & (1 << MMENU)) {
  cmnd->size_cmnd = scan_driver(cmnd->command, SBUFF, "submit");

    for (size_t i = 0; i < arrsize; i++) {
      if (string_comp(cmnd->command, items[i].cmnd, cmnd->size_cmnd)) {
        cmnd->main_byte ^= (1 << items[i].byte); match = 1;
      }
    }
    if (!match)
      System_Message("invalid option, try again");
  }
}

static void command_main(cmnd_t *cmnd) {
  while (cmnd->main_byte & (1 << MMENU)) {
    command_scanner(cmnd, main_items, ARRAY_SIZE(main_items));
  }
  return;
}

int8_t command_driver(cmnd_t *cmnd) {
  System_Message("Inside command_driver");
  Render_Header("MAIN", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");

  cmnd->main_byte |= (1 << MMENU);

  while (cmnd->main_byte & (1 << MMENU))
    command_main(cmnd);
  return SUCC;
}