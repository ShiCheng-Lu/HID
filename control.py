import usb.core
import usb.util
import struct


class MatchHIDProtocol:
    KEYBOARD = 0x01
    MOUSE = 0x02

    def __init__(self, protocol):
        self.protocol = protocol

    def __call__(self, device) -> bool:
        interface = device[0][(0, 0)]
        return (interface.bInterfaceProtocol == self.protocol)


class KeyboardControl:
    def __init__(self):
        self.device = usb.core.find(idVendor=0x16c0, idProduct=0x27da,
                                    custom_match=MatchHIDProtocol(MatchHIDProtocol.KEYBOARD))


class MouseControl:
    def __init__(self):
        self.device = usb.core.find(idVendor=0x16c0, idProduct=0x27da,
                                    custom_match=MatchHIDProtocol(MatchHIDProtocol.MOUSE))

    def move(self, button, x, y):
        self.device.ctrl_transfer(
            0x21,  # REQUEST_TYPE_CLASS | RECIPIENT_INTERFACE | ENDPOINT_OUT
            9,     # SET_REPORT
            0x200,  # "Vendor" Descriptor Type + 0 Descriptor Index
            1,     # USB interface # 0
            # the HID payload as a byte array -- e.g. from struct.pack()
            struct.pack("<Bbb", button, x, y),
        )

