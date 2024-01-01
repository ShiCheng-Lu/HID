#include <stdbool.h>
#include <stdint.h>

extern uint8_t mouse_report_descriptor[];
extern uint8_t mouse_report_descriptor_len;

typedef struct MouseReport {
    uint8_t primary : 1;
    uint8_t secondary : 1;
    uint8_t tertary : 1;
    uint8_t x;
    uint8_t y;
} MouseReport;
