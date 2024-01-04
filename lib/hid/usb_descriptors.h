// standard descriptors for the USB specification
// assumes uint16_t are packed in little endian order
// descriptor types and length are auto populated with send(descriptor);
// function
#ifndef _USB_DESCRIPTOR_H_
#define _USB_DESCRIPTOR_H_

#include "stdint.h"

// current supported descriptor types
typedef enum DescriptorType {
    DEVICE_DESCRIPTOR = 0x01,
    CONFIGURATION_DESCRIPTOR = 0x02,
    INTERFACE_DESCRIPTOR = 0x04,
    ENDPOINT_DESCRIPTOR = 0x05,
    HID_DESCRIPTOR = 0x21,
    REPORT_DESCRIPTOR = 0x22,
} __attribute__((packed)) DescriptorType;

typedef struct DescriptorHeader_t {
    uint8_t bLength;
    uint8_t bDescriptorType;
} __attribute__((packed)) DescriptorHeader_t;

#define DEVICE_DESCRIPTOR_HEADER               \
    {                                          \
        .bLength = sizeof(DeviceDescriptor_t), \
        .bDescriptorType = DEVICE_DESCRIPTOR   \
    }
typedef struct DeviceDescriptor_t {
    DescriptorHeader_t header;
    uint16_t bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t iManufacturer;
    uint8_t iProduct;
    uint8_t iSerialNumber;
    uint8_t bNumConfigurations;
} __attribute__((packed)) DeviceDescriptor_t;

#define CONFIG_DESCRIPTOR_HEADER                      \
    {                                                 \
        .bLength = sizeof(ConfigurationDescriptor_t), \
        .bDescriptorType = CONFIGURATION_DESCRIPTOR   \
    }
typedef struct ConfigurationDescriptor_t {
    DescriptorHeader_t header;
    uint16_t wTotalLength;
    uint8_t bNumInterfaces;
    uint8_t bConfigurationValue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;
    uint8_t bMaxPower;
} __attribute__((packed)) ConfigurationDescriptor_t;

#define INTERFACE_DESCRIPTOR_HEADER                   \
    {                                                 \
        .bLength = sizeof(ConfigurationDescriptor_t), \
        .bDescriptorType = INTERFACE_DESCRIPTOR       \
    }
typedef struct InterfaceDescriptor_t {
    DescriptorHeader_t header;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;  // (3 = HID)
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} __attribute__((packed)) InterfaceDescriptor_t;

#define ENDPOINT_DESCRIPTOR_HEADER               \
    {                                            \
        .bLength = sizeof(EndpointDescriptor_t), \
        .bDescriptorType = ENDPOINT_DESCRIPTOR   \
    }
typedef struct EndpointDescriptor_t {
    DescriptorHeader_t header;
    uint8_t bEndpointAddress;  // bit 7 descript flow direction, 1 = IN, 0 = OUT
    uint8_t bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;
} __attribute__((packed)) EndpointDescriptor_t;

#define HID_DESCRIPTOR_HEADER \
    { .bLength = sizeof(HIDDescriptor_t), .bDescriptorType = HID_DESCRIPTOR, }
typedef struct HIDDescriptor_t {
    DescriptorHeader_t header;
    uint16_t bcdHID;  // bcd each byte is 0-9
    uint8_t bCountryCode;
    uint8_t bNumDescriptors;
    uint8_t bDescriptorType;
    uint16_t wDescriptorLength;
} __attribute__((packed)) HIDDescriptor_t;

typedef uint8_t* StringDescriptor;

#define ENDPOINT_IN(addr)

#endif  // _USB_DESCRIPTOR_H_
