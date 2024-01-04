#include "hid/hid.h"
#include "hid/usb_descriptors.h"

#include "Descriptors.h"

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
  
  REPORT_COUNT (5)
  REPORT_SIZE (1)
  USAGE_PAGE (LEDs)
  USAGE_MINIMUM (0x01) // Num_Lock
  USAGE_MAXIMUM (0x05) // Kana
  OUTPUT (Data,Var,Abs)
  
  REPORT_COUNT (1)
  REPORT_SIZE (3)
  OUTPUT (Cnst,Var,Abs)
  
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

// uint8_t input_command_descriptor[] = {
// USAGE_PAGE (Generic_Desktop)
// USAGE ()
// COLLECTION (Application)
//   USAGE ()
//   COLLECTION ()
  
//   END_COLLECTION
// END_COLLECTION
// };

// clang-format on

DeviceDescriptor_t device_descriptor = {
    .bcdUSB = 0x0100,
    .bMaxPacketSize0 = 0x08,
    .idVendor = 0x16c0,  // using VUSB's free vendor/product ids
    .idProduct = 0x27da,
    .bNumConfigurations = 1,
};

USB_Descriptor_Configuration_t config_descriptor = {
    .Config =
        {
            .header = CONFIG_DESCRIPTOR_HEADER,
            .bNumInterfaces = 2,
            .bConfigurationValue = 1,
            // 7 bus powered, 6 self powered, 5 remote wakeup
            .bmAttributes = 0x80,
        },
    .KeyboardInterface =
        {
            .header = INTERFACE_DESCRIPTOR_HEADER,
            .bInterfaceNumber = 0,
            .bNumEndpoints = 1,
            .bInterfaceClass = 0x03,     // HID
            .bInterfaceSubClass = 0x01,  // suport Boot
            .bInterfaceProtocol = 0x01,  // keyboard
        },

    .KeyboardHID =
        {
            .bcdHID = 0x0101,
            .bNumDescriptors = 1,
            .bDescriptorType = 0x22,
            .wDescriptorLength = sizeof(keyboard_report_descriptor),
        },
    .KeyboardReportEndpoint =
        {
            // bit 7 = 1: IN, 0: OUT, bits 0-3 endpoint num
            .bEndpointAddress = KEYBOARD_IN_EPADDR,
            // 0 Control, 1 Isochronous, 2 Bulk, 3 Interrupt
            .bmAttributes = 0x03,
            .wMaxPacketSize = 0x08,
            .bInterval = 10,
        },
    .MouseInterface =
        {
            .bInterfaceNumber = 1,
            .bNumEndpoints = 1,
            .bInterfaceClass = 0x03,
            .bInterfaceSubClass = 0x01,
            .bInterfaceProtocol = 0x02,  // Mouse

        },
    .MouseHID =
        {
            .bcdHID = 0x0101,
            .bNumDescriptors = 1,
            .bDescriptorType = 0x22,
            .wDescriptorLength = sizeof(mouse_report_descriptor),
        },

    .MouseReportEndpoint =
        {
            .bEndpointAddress = MOUSE_IN_EPADDR,
            .bmAttributes = 0x03,
            .wMaxPacketSize = 0x08,
            .bInterval = 10,
        },
};



uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress) {
    const uint8_t DescriptorType = (wValue >> 8);
    // const uint8_t DescriptorNumber = (wValue & 0xFF);

    void* Address = NULL;
    uint16_t Size = NO_DESCRIPTOR;

    switch (DescriptorType) {
        case DTYPE_Device:
            Address = (void*)&device_descriptor;
            Size = sizeof(DeviceDescriptor_t);
            break;
        case DTYPE_Configuration:
            Address = (void*)&config_descriptor;
            Size = sizeof(ConfigurationDescriptor_t);
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
                    Address = &config_descriptor.KeyboardHID;
                    Size = sizeof(USB_HID_Descriptor_HID_t);
                    break;
                case INTERFACE_ID_Mouse:
                    Address = &config_descriptor.MouseHID;
                    Size = sizeof(USB_HID_Descriptor_HID_t);
                    break;
            }

            break;
        case HID_DTYPE_Report:
            switch (wIndex) {
                case INTERFACE_ID_Keyboard:
                    Address = &keyboard_report_descriptor;
                    Size = sizeof(keyboard_report_descriptor);
                    break;
                case INTERFACE_ID_Mouse:
                    Address = &mouse_report_descriptor;
                    Size = sizeof(mouse_report_descriptor);
                    break;
            }

            break;
    }

    *DescriptorAddress = Address;
    return Size;
}
