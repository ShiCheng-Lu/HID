#ifndef _HID_ITEMS_H_
#define _HID_ITEMS_H_

// ORs all datatypes together, maximum of 8 flags
#define DT(a, b, c, d, e, f, g, h, ...) \
  DT_##a | DT_##b | DT_##c | DT_##d | DT_##e | DT_##f | DT_##g | DT_##h

// clang-format off

// Main items
#define INPUT(...)              0x81, DT(__VA_ARGS__,,,,,,,,),
#define OUTPUT(...)             0x91, DT(__VA_ARGS__,,,,,,,,),
#define FEATURE(...)            0xB1, DT(__VA_ARGS__,,,,,,,,),
#define COLLECTION(a)           0xA1, CT_##a,
#define END_COLLECTION          0xC0,
// Global items
#define USAGE_PAGE(a)           0x05, UPG_##a,
#define LOGICAL_MINIMUM(a)      0x15, a,
#define LOGICAL_MAXIMUM(a)      0x25, a,
#define PHYSICAL_MINIMUM(a)     0x35, a,
#define PHYSICAL_MAXIMUM(a)     0x45, a,
#define UNIT_EXPONENT
#define UNIT
#define REPORT_SIZE(a)          0x75, a,
#define REPORT_ID
#define REPORT_COUNT(a)         0x95, a,
#define PUSH
#define POP
// Local items
#define USAGE(a)                0x09, a,
#define USAGE_MINIMUM(a)        0x19, a,
#define USAGE_MAXIMUM(a)        0x29, a,
#define DESIGNATOR_INDEX
#define DESIGNATOR_MINIMUM
#define DESIGNATOR_MAXIMUM
#define STRING_INDEX
#define STRING_MINIMUM
#define STRING_MAXIMUM
#define DELIMITER

// clang-format on

#endif  // _HID_ITEMS_H_
