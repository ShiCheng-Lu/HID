#include "hid/hid.h"
#include "keyboard_hid.h"

// clang-format off
uint8_t keyboard_report_descriptor[] = {

USAGE_PAGE (Generic_Desktop)
USAGE (Keyboard)
COLLECTION (Application)
  USAGE_PAGE (Keyboard)
  USAGE_MINIMUM (Keyboard_LeftControl)
  USAGE_MAXIMUM (Keyboard_Right_GUI)
  LOGICAL_MINIMUM (0)
  LOGICAL_MAXIMUM (1)
  REPORT_SIZE (1)
  REPORT_COUNT (8)
  INPUT (Data,Var,Abs)
  
  REPORT_COUNT (1)
  REPORT_SIZE (8)
  INPUT (Cnst,Var,Abs)
  
  // REPORT_COUNT (5)
  // REPORT_SIZE (1)
  // USAGE_PAGE (LEDs)
  // USAGE_MINIMUM (Num_Lock)
  // USAGE_MAXIMUM (Kana)
  // OUTPUT (Data,Var,Abs)
  
  // REPORT_COUNT (1)
  // REPORT_SIZE (3)
  // OUTPUT (Cnst,Var,Abs)
  
  REPORT_COUNT (6)
  REPORT_SIZE (8)
  LOGICAL_MAXIMUM (0)
  LOGICAL_MAXIMUM (101)
  USAGE_PAGE (Keyboard)
  USAGE_MINIMUM (0)
  USAGE_MAXIMUM (Keyboard_Application)
  INPUT (Data,Ary,Abs)
END_COLLECTION
};

size_t keyboard_report_descriptor_len = sizeof(keyboard_report_descriptor);
