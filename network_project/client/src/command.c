#include "scan.h"
#include "command.h"

uint8_t static ENTRY = 0x00;

static const char *BEGIN_CMND[] = {
  "-fetch data", "-steer device", "-quit"
};
static const char *FETCH_CMND[] = {
  "-temperature", "humidity", "-back"
};
static const char *STEER_CMND[] = {
  "-red", "-blue", "-green", "-back"
};

static uint8_t begin_cmnd(char *command) {

  scan = scan_driver("choose entry");
}

static void fetch_cmnd(char *command) {

}

static void steer_cmnd(char *command) {

}

typedef void (*cmnd_func)(char *command);

typedef struct {
  cmnd_func func;
} cmnd_item;

static cmnd_item cmnd_items[] = {
  {begin_cmnd}, {fetch_cmnd}, {steer_cmnd}
};

void command_driver(size_t size, char *command) {

}
