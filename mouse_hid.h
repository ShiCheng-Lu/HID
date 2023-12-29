#include <stdbool.h>
#include <stdint.h>

extern uint8_t mouse_report_descriptor[];
extern size_t mouse_report_descriptor_len;

typedef struct MouseReport {
  bool primary : 1;
  bool secondary : 1;
  bool tertary : 1;
  // should be autopadded for x to be byte aligned
  int8_t x;
  int8_t y;
} MouseReport;
