#include "hid/hid.h"
#include "hid/usb_descriptors.h"

#include "Descriptors.h"

// clang-format off
const uint8_t PROGMEM keyboard_report_descriptor[] = {
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
    INPUT (Cnst)
  
    // REPORT_COUNT (5)
    // REPORT_SIZE (1)
    // USAGE_PAGE (LEDs)
    // USAGE_MINIMUM (0x01) // Num_Lock
    // USAGE_MAXIMUM (0x05) // Kana
    // OUTPUT (Data,Var,Abs)
    
    // REPORT_COUNT (1)
    // REPORT_SIZE (3)
    // OUTPUT (Cnst)
  
    REPORT_COUNT (6)
    REPORT_SIZE (8)
    LOGICAL_MAXIMUM (0)
    LOGICAL_MAXIMUM (101)
    USAGE_PAGE (Keyboard)
    USAGE_MINIMUM (0)
    USAGE_MAXIMUM (Keyboard_Application)
    INPUT (Data,Ary,Abs)

    USAGE_PAGE (Generic_Desktop)
    USAGE (0x01)
    LOGICAL_MINIMUM (0x00)
    LOGICAL_MAXIMUM (0xFF)
    REPORT_SIZE (8)
    REPORT_COUNT (sizeof(KeyboardReport_t))
    OUTPUT (Data,Var,Abs)
END_COLLECTION
};

const uint8_t PROGMEM mouse_report_descriptor[] = {
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
        LOGICAL_MINIMUM (-128)
        LOGICAL_MAXIMUM (127)
        PHYSICAL_MINIMUM (-5)
        PHYSICAL_MAXIMUM (5)
        REPORT_SIZE (8)
        REPORT_COUNT (2)
        INPUT (Data,Var,Rel)
    END_COLLECTION
  
    USAGE_PAGE (Generic_Desktop)
    USAGE (0x01)
    LOGICAL_MINIMUM (0x00)
    LOGICAL_MAXIMUM (0xFF)
    REPORT_SIZE (8)
    REPORT_COUNT (sizeof(MouseReport_t))
    OUTPUT (Data,Var,Abs)
END_COLLECTION
};

// clang-format on

const DeviceDescriptor_t PROGMEM device_descriptor = {
    .header = DEVICE_DESCRIPTOR_HEADER,
    .bcdUSB = VERSION_BCD(1, 1, 0),
    .bMaxPacketSize0 = 0x08,
    .idVendor = 0x16c0,  // using VUSB's free vendor/product ids
    .idProduct = 0x27da,
    .bcdDevice = VERSION_BCD(0, 0, 1),
    .bNumConfigurations = 1,
};

const USB_Descriptor_Configuration_t PROGMEM config_descriptor = {
    .Config =
        {
            .header = CONFIG_DESCRIPTOR_HEADER,
            .wTotalLength = sizeof(USB_Descriptor_Configuration_t),
            .bNumInterfaces = 2,
            .bConfigurationValue = 1,
            // 7 bus powered, 6 self powered, 5 remote wakeup
            .bmAttributes = 0x80,
            .bMaxPower = USB_CONFIG_POWER_MA(100),
        },

    .KeyboardInterface =
        {
            .header = INTERFACE_DESCRIPTOR_HEADER,
            .bInterfaceNumber = INTERFACE_ID_Keyboard,
            .bNumEndpoints = 2,
            .bInterfaceClass = 0x03,     // HID
            .bInterfaceSubClass = 0x01,  // suport Boot
            .bInterfaceProtocol = 0x01,  // keyboard
        },
    .KeyboardHID =
        {
            .header = HID_DESCRIPTOR_HEADER,
            .bcdHID = VERSION_BCD(1, 1, 1),
            .bNumDescriptors = 1,
            .bDescriptorType = REPORT_DESCRIPTOR,
            .wDescriptorLength = sizeof(keyboard_report_descriptor),
        },
    .KeyboardReportInEndpoint =
        {
            .header = ENDPOINT_DESCRIPTOR_HEADER,
            // bit 7 = 1: IN, 0: OUT, bits 0-3 endpoint num
            .bEndpointAddress = KEYBOARD_IN_EPADDR,
            // 0 Control, 1 Isochronous, 2 Bulk, 3 Interrupt
            .bmAttributes = 0x03,
            .wMaxPacketSize = 0x08,
            .bInterval = 5,
        },
    .KeyboardReportOutEndpoint =
        {
            .header = ENDPOINT_DESCRIPTOR_HEADER,
            .bEndpointAddress = KEYBOARD_OUT_EPADDR,
            .bmAttributes = 0x03,
            .wMaxPacketSize = 0x08,
            .bInterval = 5,
        },

    .MouseInterface =
        {
            .header = INTERFACE_DESCRIPTOR_HEADER,
            .bInterfaceNumber = INTERFACE_ID_Mouse,
            .bNumEndpoints = 2,
            .bInterfaceClass = 0x03,
            .bInterfaceSubClass = 0x01,
            .bInterfaceProtocol = 0x02,  // Mouse
        },
    .MouseHID =
        {
            .header = HID_DESCRIPTOR_HEADER,
            .bcdHID = VERSION_BCD(1, 1, 1),
            .bNumDescriptors = 1,
            .bDescriptorType = REPORT_DESCRIPTOR,
            .wDescriptorLength = sizeof(mouse_report_descriptor),
        },
    .MouseReportInEndpoint =
        {
            .header = ENDPOINT_DESCRIPTOR_HEADER,
            .bEndpointAddress = MOUSE_IN_EPADDR,
            .bmAttributes = 0x03,
            .wMaxPacketSize = 0x08,
            .bInterval = 5,
        },
    .MouseReportOutEndpoint =
        {
            .header = ENDPOINT_DESCRIPTOR_HEADER,
            .bEndpointAddress = MOUSE_OUT_EPADDR,
            .bmAttributes = 0x03,
            .wMaxPacketSize = 0x08,
            .bInterval = 5,
        },
};

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress) {
    const uint8_t DescriptorType = (wValue >> 8);
    const uint8_t DescriptorNumber = (wValue & 0xFF);

    void* Address = NULL;
    uint16_t Size = 0;

    switch (DescriptorType) {
        case DTYPE_Device:
            Address = (void*)&device_descriptor;
            Size = sizeof(DeviceDescriptor_t);
            break;
        case DTYPE_Configuration:
            Address = (void*)&config_descriptor;
            Size = sizeof(USB_Descriptor_Configuration_t);
            break;
        // case DTYPE_String:
        //     switch (DescriptorNumber) {
        //         case STRING_ID_Language:
        //             Address = &LanguageString;
        //             Size = pgm_read_byte(&LanguageString.Header.Size);
        //             break;
        //         case STRING_ID_Manufacturer:
        //             Address = &ManufacturerString;
        //             Size = pgm_read_byte(&ManufacturerString.Header.Size);
        //             break;
        //         case STRING_ID_Product:
        //             Address = &ProductString;
        //             Size = pgm_read_byte(&ProductString.Header.Size);
        //             break;
        //     }

        //     break;
        case HID_DTYPE_HID:
            switch (wIndex) {
                case INTERFACE_ID_Keyboard:
                    Address = (void*)&config_descriptor.KeyboardHID;
                    Size = sizeof(HIDDescriptor_t);
                    break;
                case INTERFACE_ID_Mouse:
                    Address = (void*)&config_descriptor.MouseHID;
                    Size = sizeof(HIDDescriptor_t);
                    break;
            }

            break;
        case HID_DTYPE_Report:
            switch (wIndex) {
                case INTERFACE_ID_Keyboard:
                    Address = (void*)&keyboard_report_descriptor;
                    Size = sizeof(keyboard_report_descriptor);
                    break;
                case INTERFACE_ID_Mouse:
                    Address = (void*)&mouse_report_descriptor;
                    Size = sizeof(mouse_report_descriptor);
                    break;
            }

            break;
    }

    *DescriptorAddress = Address;
    return Size;
}
