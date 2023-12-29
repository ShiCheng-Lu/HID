#include "mouse_hid.h"
#include "hid/hid.h"

// clang-format off
uint8_t mouse_report_descriptor[] = {

USAGE_PAGE (Generic_Desktop) 
USAGE (Mouse)
COLLECTION (Application)
  USAGE (Pointer)
  COLLECTION (Physical)
    USAGE_PAGE (Button)
    USAGE_MINIMUM (Button_1)
    USAGE_MAXIMUM (Button_3)
    LOGICAL_MINIMUM (0)
    LOGICAL_MAXIMUM (1)
    REPORT_COUNT (3)
    REPORT_SIZE (1)
    INPUT (Data,Var,Abs)
    REPORT_COUNT (1)
    REPORT_SIZE (5)
    INPUT (Cnst,Var,Abs)
    USAGE_PAGE (Generic_Desktop)
    USAGE (X)
    USAGE (Y)
    LOGICAL_MINIMUM (-127)
    LOGICAL_MAXIMUM (127)
    REPORT_SIZE (8)
    REPORT_COUNT (2)
    INPUT (Data,Var,Rel)
  END_COLLECTION
END_COLLECTION

};

size_t mouse_report_descriptor_len = sizeof(mouse_report_descriptor);
