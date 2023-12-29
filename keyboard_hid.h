#include <stdbool.h>
#include <stdint.h>

extern uint8_t keyboard_report_descriptor[];
extern size_t keyboard_report_descriptor_len;

typedef struct KeyboardReport {
  bool left_control : 1;
  bool left_shift : 1;
  bool left_alt : 1;
  bool left_gui : 1;
  bool right_control : 1;
  bool right_shift : 1;
  bool right_alt : 1;
  bool right_gui : 1;
  uint8_t reserved;
  uint8_t keys[6];
} KeyboardReport;
