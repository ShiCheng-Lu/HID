/*
             LUFA Library
     Copyright (C) Dean Camera, 2021.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2021  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include "Descriptors.h"
#include "SerialInterface.h"
#include "UsbEvents.h"

void SetKeyboardReport(KeyboardReport_t* keyboard) {}

void HandleLEDsReport(uint8_t* leds) {
    uint8_t LEDMask = 0;
    if (*leds & HID_KEYBOARD_LED_NUMLOCK)
        LEDMask |= LEDS_LED1;

    if (*leds & HID_KEYBOARD_LED_CAPSLOCK)
        LEDMask |= LEDS_LED3;

    if (*leds & HID_KEYBOARD_LED_SCROLLLOCK)
        LEDMask |= LEDS_LED4;

    LEDs_SetAllLEDs(LEDMask);
}

/** Configures the board hardware and chip peripherals for the demo's
 * functionality. */
void SetupHardware(void) {
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    // clock_prescale_set(clock_div_1);

    /* Hardware Initialization */
    Serial_Init(9600, false);
    LEDs_Init();
    USB_Init();

    /* Start the flush timer so that overflows occur rapidly to push received
     * bytes to the USB interface */
    TCCR0B = (1 << CS02);

    /* Pull target /RESET line high */
    // AVR_RESET_LINE_PORT |= AVR_RESET_LINE_MASK;
    // AVR_RESET_LINE_DDR  |= AVR_RESET_LINE_MASK;
}

int main(void) {
    SetupHardware();

    GlobalInterruptEnable();

    int counter = 0;
    for (;;) {
        Read_UART_Task();
        HID_USBTask();
        USB_USBTask();
        if (counter++ > 1000) {
            Serial_SendByte(1);
            counter = 0;
        }
    }
}
