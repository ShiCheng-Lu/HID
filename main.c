#include "mouse_hid.h"
#include "stdio.h"
#include "usb/usb_descriptors.h"

DeviceDescriptor device_descriptor;
ConfigurationDescriptor config_descriptor;
InterfaceDescriptor interface_descriptor;
EndpointDescriptor endpoint_descriptor;

HIDDescriptor hid_descriptor;

void setup(void) {
  send_descriptor(&device_descriptor, DEVICE_DESCRIPTOR);
  send_descriptor(&config_descriptor, CONFIGURATION_DESCRIPTOR);
  send_descriptor(&interface_descriptor, INTERFACE_DESCRIPTOR);
  send_descriptor(&endpoint_descriptor, ENDPOINT_DESCRIPTOR);

  // send(hid_descriptor);
  send(mouse_report_descriptor, mouse_report_descriptor_len);
}

uint8_t buffer[64];

void interrupt(void) {
  // receive(buffer);
}

MouseReport mouse_report = {
    .primary = false,
    .secondary = false,
    .tertary = true,
    .x = 5,
    .y = 10,
};

void main(void) {
  setup();

  send((uint8_t*)&mouse_report, sizeof(mouse_report));

  // while (1) {
  // }
}
