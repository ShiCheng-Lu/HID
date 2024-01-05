
import usb.core
import usb.util

# Find our device
# dev = usb.core.find(idVendor=0xfffe, idProduct=0x0001)
dev = usb.core.find(idVendor=0x16c0, idProduct=0x27da)

# Was it found?
if dev is None:
    raise ValueError('Device not found')

dev.set_configuration()

cfg = dev[0]
intf = cfg[(0,0)]
ep = intf[0]

# dev.write(ep.bEndpointAddress, [0x00, 0x00,0x04,0x04,0xFF,0xFF,0xFF,0x00, 0x00], 1000)
# dev.ctrl_transfer(bmRequestType, bRequest, wValue=0, wIndex=0, data_or_wLength=None, timeout=None)

print("print ep")
print(ep)
print("print cfg")
print(cfg)
print("print intf")
print(intf)

while True:
    pass
