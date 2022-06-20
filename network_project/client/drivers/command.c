

/*---------------------------------------------------------------------------------------------------------------Task Byte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |    -    |    -    |    -    |    -    |    -    |     -    |   TDVCE   |   TMESG   |
                                    --------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------Execute Byte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |    -    |  RWBIT  |  EXEC5  |  EXEC4  |  EXEC3  |   EXEC2  |   EXEC1   |   EXEC0   |
                                    --------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------Forward Byte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |    -    |  FBIT6  |  FBIT5  |  FBIT4  |  FBIT3  |   FBIT2  |   FBIT1   |   FBIT0   |
------------------------------------------------------------------------------------------------------------------------*/

#include "scanner.h"
#include "cstring.h"
#include "command.h"

static int8_t TASK = 0x00;
static int8_t EXEC = 0x00;
static int8_t FWRD = 0x00;

static int8_t current_state = _MAIN; 

typedef struct CmndItem {
  const int8_t state;
  const char *cmnd;
} cmnd_item;

static cmnd_item main[] = {
  {_MESG, "-message"}, {_DVCE, "-device"}, {_EXIT, "-exit"}
};
static cmnd_item mesg[] = {
  {_EXIT, "-send"}, {_EXIT, "-read"}, {_MAIN, "-back"}
};
static cmnd_item dvce[] = {
  {_EXIT, "-red"}, {_EXIT, "-blue"}, {_EXIT, "-green"}, {_MAIN, "-back"}
};

static void static_cleanup(void) {
  TASK = 0x00, EXEC = 0x00, FWRD = 0x00;
}
static void render_options(cmnd_item *items, size_t size_array) {
  for (size_t i = 0; i < size_array; i++)
    printf("\t%s\n", items[i].cmnd);
}
static int8_t command_scan(cmnd_item *items, size_t size_array) {
  render_options(items, size_array);

  char command[SBUFF] = {'\0'};
  size_t cmnd_size = scan_driver(command, SBUFF, "select");

  for (size_t i = 0; i < size_array; i++) {
    if (string_comp(command, items[i].cmnd, cmnd_size)) {
      return items[i].state;
    }
  }
  System_Message("Not an option. try again");
  return current_state;
}

static int8_t command_main(cmnd_item *main, size_t size_array) {
  Render_Header("MAIN", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
  return command_scan(main, size_array);
}

static int8_t command_mesg(cmnd_item *mesg, size_t size_array) {
  Render_Header("Message", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");

  TASK &= ~(1 << TDVCE), TASK |= (1 << TMESG);
  return command_scan(mesg, size_array);
}

static int8_t command_dvce(cmnd_item *dvce, size_t size_array) {
  Render_Header("Device", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
  
  TASK &= ~(1 << TMESG), TASK |= (1 << TDVCE);
  PrintByte(TASK);
  return command_scan(dvce, size_array);
}

int8_t command_driver(cmnd_t *cmnd) {

  System_Message("Inside command driver");

  while (current_state != _EXIT) {

    switch(current_state) {
    case _MAIN:
      current_state = command_main(main, ARRAY_SIZE(main));
      break;
    case _MESG:
      current_state = command_mesg(mesg, ARRAY_SIZE(mesg));
      break;
    case _DVCE:
      current_state = command_dvce(dvce, ARRAY_SIZE(dvce));
      break;
    }
  }

  cmnd->protocol[0] = FWRD;
  cmnd->protocol[1] = EXEC;
  cmnd->protocol[2] = TASK;

  static_cleanup();

  return SUCC;
}

/*
static cmnd_item main[] = {
  {_MESG, TMESG, "-message"}, {_DVCE, TDVCE, "-device"}, {_EXIT, CLEAR, "-exit"}
};
static cmnd_item mesg[] = {
  {_EXIT, RWBIT, "-send"}, {_EXIT, RWBIT, "-read"}, {_MAIN, CLEAR, "-back"}
};
static cmnd_item dvce[] = {
  {_EXIT, EXEC0, "-red"}, {_EXIT, EXEC1, "-blue"}, {_EXIT, EXEC0"-green"}, {_MAIN, CLEAR, "-back"}
};
*/