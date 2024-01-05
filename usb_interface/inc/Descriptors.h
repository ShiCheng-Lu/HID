/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.

  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

/* Includes: */
#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>

#include "hid/usb_descriptors.h"

/* Type Defines: */
/** Type define for the device configuration descriptor structure. This must be
 * defined in the application code, as the configuration descriptor contains
 * several sub-descriptors which vary between devices, and which describe the
 * device's usage to the host.
 */
typedef struct {
    ConfigurationDescriptor_t Config;

    // Keyboard HID Interface
    InterfaceDescriptor_t KeyboardInterface;
    HIDDescriptor_t KeyboardHID;
    EndpointDescriptor_t KeyboardReportEndpoint;

    // Mouse HID Interface
    InterfaceDescriptor_t MouseInterface;
    HIDDescriptor_t MouseHID;
    EndpointDescriptor_t MouseReportEndpoint;
} USB_Descriptor_Configuration_t;

typedef struct KeyboardReport_t {
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
} KeyboardReport_t;

typedef struct MouseReport_t {
    uint8_t buttons;
    int8_t x;
    int8_t y;
} MouseReport_t;

enum {
    INTERFACE_ID_Keyboard = 0, /**< Keyboard interface descriptor ID */
    INTERFACE_ID_Mouse = 1,    /**< Mouse interface descriptor ID */
};

/** Endpoint address of the Keyboard HID reporting IN endpoint. */
#define KEYBOARD_IN_EPADDR (ENDPOINT_DIR_IN | 1)

/** Endpoint address of the Mouse HID reporting IN endpoint. */
#define MOUSE_IN_EPADDR (ENDPOINT_DIR_IN | 3)

/** Size in bytes of each of the HID reporting IN endpoints. */
#define HID_EPSIZE 8

/* Function Prototypes: */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress)
    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
