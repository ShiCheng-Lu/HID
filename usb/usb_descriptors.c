#include <stdio.h>

#include "string.h"
#include "usb_descriptors.h"

void send(uint8_t* bytes, size_t length) {
  // just print out the bytes to terminal
  for (size_t i = 0; i < length; ++i) {
    printf("%.2x ", bytes[i]);
  }
  printf("\n");
}

uint8_t prv_size_of(DescriptorType type) {
  switch (type) {
    case DEVICE_DESCRIPTOR:
      return sizeof(DeviceDescriptor);
    case CONFIGURATION_DESCRIPTOR:
      return sizeof(ConfigurationDescriptor);
    case INTERFACE_DESCRIPTOR:
      return sizeof(InterfaceDescriptor);
    case ENDPOINT_DESCRIPTOR:
      return sizeof(EndpointDescriptor);

    default:
      return 0;
  }
}

void send_descriptor(void* descriptor, DescriptorType type) {
  uint8_t* data = (uint8_t*)descriptor;
  data[0] = prv_size_of(type);
  data[1] = type;
  send(data, data[0]);
}
