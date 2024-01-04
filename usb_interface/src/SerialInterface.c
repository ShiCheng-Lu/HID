
#include <LUFA/Drivers/Peripheral/Serial.h>
#include <LUFA/Drivers/USB/USB.h>

#include "UsbEvents.h"

static int counter = 0;
volatile MouseReport_t mouse;

enum {
    ZERO,
    POS_SLOW,
    POS_MEDIUM,
    POS_FAST,
    NEG_SLOW,
    NEG_MEDIUM,
    NEG_FAST,
};

int8_t speed(uint8_t data) {
    switch (data) {
        case ZERO:
            return 0;
        case POS_SLOW:
            return 1;
        case POS_MEDIUM:
            return 2;
        case POS_FAST:
            return 3;
        case NEG_SLOW:
            return -1;
        case NEG_MEDIUM:
            return -2;
        case NEG_FAST:
            return -3;
        default:
            return 0;
    }
}

void Read_UART_Task(void) {
    int16_t byte = Serial_ReceiveByte();
    if (byte == -1) {
        return;
    }
    if (byte == 0xff) {
        counter = 0;
        return;
    }
    if (counter == 0) {
        mouse.buttons = (byte != 0);
    } else if (counter == 1) {
        mouse.x = speed(byte);
    } else if (counter == 2) {
        mouse.y = speed(byte);
    }
    counter++;
}

void SetMouseReport(MouseReport_t* dest) {
    dest->x = mouse.x;
    dest->y = mouse.y;
}
