
#include <LUFA/Drivers/Peripheral/Serial.h>
#include <LUFA/Drivers/USB/USB.h>

#include "UsbEvents.h"

static uint8_t counter = 1;
static uint8_t data_size = 0;
static uint8_t type = 0;

static MouseReport_t mouse;
static KeyboardReport_t keyboard;

void Read_UART_Task(void) {
    int16_t received = Serial_ReceiveByte();
    if (received == -1) {  // no data
        return;
    }
    uint8_t byte = received;
    if ((counter >= data_size) &&
        ((byte & 0xA0) == 0x80)) {  // start of message
        data_size = byte & 0x1F;
        counter = 0;
        return;
    }
    if (counter < data_size) {
        ((uint8_t*)&mouse)[counter] = byte;
        counter++;
    }
}

void SetMouseReport(MouseReport_t* data) {
    memcpy(data, &mouse, sizeof(MouseReport_t));
}

void SetKeyboardReport(KeyboardReport_t* data) {
    memcpy(data, &keyboard, sizeof(KeyboardReport_t));
}

void HandleMouseReport(MouseReport_t* data) {
    memcpy(&mouse, data, sizeof(MouseReport_t));
}

void HandleKeyboardReport(KeyboardReport_t* data) {
    memcpy(&keyboard, data, sizeof(KeyboardReport_t));
}
