import usb.core
import usb.util
import struct


class MatchHIDProtocol:
    '''filter usb device based on the HID protocol'''
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
        self.device.set_configuration()
        self.interface = self.device[0][(0, 0)].bInterfaceNumber

    def report(self, modifier, keys):
        pass


class MouseControl:
    def __init__(self):
        self.device = usb.core.find(idVendor=0x16c0, idProduct=0x27da,
                                    custom_match=MatchHIDProtocol(MatchHIDProtocol.MOUSE))
        self.device.set_configuration()
        self.interface = self.device[0][(0, 0)].bInterfaceNumber

    def report(self, button, x, y):
        self.device.ctrl_transfer(
            0x21,  # REQUEST_TYPE_CLASS | RECIPIENT_INTERFACE | ENDPOINT_OUT
            9,     # SET_REPORT
            0x200,  # "Vendor" Descriptor Type + 0 Descriptor Index
            self.interface,     # USB interface
            # the HID payload as a byte array -- e.g. from struct.pack()
            struct.pack("<Bbb", button, x, y),
        )
    
    def move(self, x, y):
        pass


keyboard = KeyboardControl()
mouse = MouseControl()
