// standard descriptors for the USB specification
// assumes uint16_t are packed in little endian order
// descriptor types and length are auto populated with send(descriptor);
// function
#ifndef _USB_DESCRIPTOR_H_
#define _USB_DESCRIPTOR_H_

#pragma pack(1)

#include "stdint.h"

// current supported descriptor types
typedef enum DescriptorType {
  DEVICE_DESCRIPTOR = 0x01,
  CONFIGURATION_DESCRIPTOR = 0x02,
  INTERFACE_DESCRIPTOR = 0x04,
  ENDPOINT_DESCRIPTOR = 0x05,
  HID_DESCRIPTOR = 0x21,
  REPORT_DESCRIPTOR = 0x22,
} DescriptorType;

typedef struct DeviceDescriptor {
  uint8_t bLength;
  uint8_t bDescriptorType;
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
} DeviceDescriptor;

typedef struct ConfigurationDescriptor {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint16_t wTotalLength;
  uint8_t bNumInterfaces;
  uint8_t bConfigurationValue;
  uint8_t iConfiguration;
  uint8_t bmAttributes;
  uint8_t bMaxPower;
} ConfigurationDescriptor;

typedef struct InterfaceDescriptor {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bInterfaceNumber;
  uint8_t bAlternateSetting;
  uint8_t bNumEndpoints;
  uint8_t bInterfaceClass;  // (3 = HID)
  uint8_t bInterfaceSubClass;
  uint8_t bInterfaceProtocol;
  uint8_t iInterface;
} InterfaceDescriptor;

typedef struct EndpointDescriptor {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bEndpointAddress;  // bit 7 descript flow direction, 1 = IN, 0 = OUT
  uint8_t bmAttributes;
  uint16_t wMaxPacketSize;
  uint8_t bInterval;
} EndpointDescriptor;

#define MAX_REPORTS 10

typedef struct HIDDescriptor {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint16_t bcdHID;  // bcd each byte is 0-9
  uint8_t bCountryCode;
  uint8_t bNumDescriptors;
  struct {
    uint8_t bDescriptorType;
    uint16_t wDescriptorLength;
  } reports[MAX_REPORTS];
} HIDDescriptor;

typedef uint8_t* StringDescriptor;

void send(uint8_t* bytes, size_t length);
void send_descriptor(void* descriptor, DescriptorType type);

#endif  // _USB_DESCRIPTOR_H_
