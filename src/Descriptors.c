#include "hid/hid.h"
#include "usb/usb_descriptors.h"



DeviceDescriptor device_descriptor = {
    .bcdUSB = 0x0100,
    .bMaxPacketSize0 = 0x08,
    .idVendor = 0x16c0,  // using VUSB's free vendor/product ids
    .idProduct = 0x27da,
    .bNumConfigurations = 1,
};
ConfigurationDescriptor config_descriptor = {
    .bNumInterfaces = 2,
    .bConfigurationValue = 1,
    .bmAttributes = 0x80,  // 7 bus powered, 6 self powered, 5 remote wakeup
};
InterfaceDescriptor keyboard_interface_descriptor = {
    .bInterfaceNumber = 0,
    .bNumEndpoints = 1,
    .bInterfaceClass = 0x03,     // HID
    .bInterfaceSubClass = 0x01,  // suport Boot
    .bInterfaceProtocol = 0x01,  // keyboard
};
EndpointDescriptor keyboard_endpoint_descriptor = {
    .bEndpointAddress = 0x81,  // bit 7 = 1: IN, 0: OUT, bits 0-3 endpoint num
    .bmAttributes = 0x03,      // 0 Control, 1 Isochronous, 2 Bulk, 3 Interrupt
    .wMaxPacketSize = 0x08,
    .bInterval = 10,
};

HIDDescriptor keyboard_hid_descriptor = {
    .bcdHID = 0x0101,
    .bNumDescriptors = 1,
    .reports[0].bDescriptorType = 0x22,
};

InterfaceDescriptor mouse_interface_descriptor = {
    .bInterfaceNumber = 1,
    .bNumEndpoints = 1,
    .bInterfaceClass = 0x03,
    .bInterfaceSubClass = 0x01,
    .bInterfaceProtocol = 0x02,  // Mouse

};
EndpointDescriptor mouse_endpoint_descriptor = {
    .bEndpointAddress = 0x82,
    .bmAttributes = 0x03,
    .wMaxPacketSize = 0x08,
    .bInterval = 10,
};
HIDDescriptor mouse_hid_descriptor = {
    .bcdHID = 0x0101,
    .bNumDescriptors = 1,
    .reports[0].bDescriptorType = 0x22,
};