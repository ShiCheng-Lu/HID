#include "UsbEvents.h"

/* Macros: */
/** LED mask for the library LED driver, to indicate that the USB interface is
 * not ready. */
#define LEDMASK_USB_NOTREADY LEDS_LED1

/** LED mask for the library LED driver, to indicate that the USB interface is
 * enumerating. */
#define LEDMASK_USB_ENUMERATING (LEDS_LED2 | LEDS_LED3)

/** LED mask for the library LED driver, to indicate that the USB interface is
 * ready. */
#define LEDMASK_USB_READY (LEDS_LED2 | LEDS_LED4)

/** LED mask for the library LED driver, to indicate that an error has occurred
 * in the USB interface. */
#define LEDMASK_USB_ERROR (LEDS_LED1 | LEDS_LED3)

/** Buffer to hold the previously generated Keyboard HID report, for comparison
 * purposes inside the HID class driver. */
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(KeyboardReport_t)];

/** Buffer to hold the previously generated Mouse HID report, for comparison
 * purposes inside the HID class driver. */
static uint8_t PrevMouseHIDReportBuffer[sizeof(MouseReport_t)];

/** LUFA HID Class driver interface configuration and state information. This
 * structure is passed to all HID Class driver functions, so that multiple
 * instances of the same class within a device can be differentiated from one
 * another. This is for the keyboard HID interface within the device.
 */
USB_ClassInfo_HID_Device_t Keyboard_HID_Interface = {
    .Config =
        {
            .InterfaceNumber = INTERFACE_ID_Keyboard,
            .ReportINEndpoint =
                {
                    .Address = KEYBOARD_IN_EPADDR,
                    .Size = HID_EPSIZE,
                    .Banks = 1,
                },
            .PrevReportINBuffer = PrevKeyboardHIDReportBuffer,
            .PrevReportINBufferSize = sizeof(PrevKeyboardHIDReportBuffer),
        },
};

/** LUFA HID Class driver interface configuration and state information. This
 * structure is passed to all HID Class driver functions, so that multiple
 * instances of the same class within a device can be differentiated from one
 * another. This is for the mouse HID interface within the device.
 */
USB_ClassInfo_HID_Device_t Mouse_HID_Interface = {
    .Config =
        {
            .InterfaceNumber = INTERFACE_ID_Mouse,
            .ReportINEndpoint =
                {
                    .Address = MOUSE_IN_EPADDR,
                    .Size = HID_EPSIZE,
                    .Banks = 1,
                },
            .PrevReportINBuffer = PrevMouseHIDReportBuffer,
            .PrevReportINBufferSize = sizeof(PrevMouseHIDReportBuffer),
        },
};

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void) {
    LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void) {
    LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void) {
    bool ConfigSuccess = true;

    ConfigSuccess &= HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);
    ConfigSuccess &= HID_Device_ConfigureEndpoints(&Mouse_HID_Interface);

    USB_Device_EnableSOFEvents();

    LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void) {
    HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
    HID_Device_ProcessControlRequest(&Mouse_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void) {
    HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
    HID_Device_MillisecondElapsed(&Mouse_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the
 * host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface
 * configuration structure being referenced \param[in,out] ReportID    Report ID
 * requested by the host if non-zero, otherwise callback should set to the
 * generated report ID \param[in]     ReportType  Type of the report to create,
 * either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature \param[out] ReportData
 * Pointer to a buffer where the created report should be stored \param[out]
 * ReportSize  Number of bytes written in the report (or zero if no report is to
 * be sent)
 *
 *  \return Boolean \c true to force the sending of the report, \c false to let
 * the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(
    USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
    uint8_t* const ReportID,
    const uint8_t ReportType,
    void* ReportData,
    uint16_t* const ReportSize) {
    /* Determine which interface must have its report generated */
    if (HIDInterfaceInfo == &Keyboard_HID_Interface) {
        KeyboardReport_t* keyboard = (KeyboardReport_t*)ReportData;

        SetKeyboardReport(keyboard);

        *ReportSize = sizeof(KeyboardReport_t);
        return false;
    } else {
        MouseReport_t* mouse = (MouseReport_t*)ReportData;

        SetMouseReport(mouse);

        *ReportSize = sizeof(MouseReport_t);
        return true;
    }
}

/** HID class driver callback function for the processing of HID reports from
 * the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface
 * configuration structure being referenced \param[in] ReportID    Report ID of
 * the received report from the host \param[in] ReportType  The type of report
 * that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has
 * been stored \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(
    USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
    const uint8_t ReportID,
    const uint8_t ReportType,
    const void* ReportData,
    const uint16_t ReportSize) {
    if (HIDInterfaceInfo == &Keyboard_HID_Interface) {
        uint8_t* LEDReport = (uint8_t*)ReportData;

        HandleLEDsReport(LEDReport);
    }
}

/**
 * 
 */
void HID_USBTask(void) {
    HID_Device_USBTask(&Keyboard_HID_Interface);
    HID_Device_USBTask(&Mouse_HID_Interface);
}
