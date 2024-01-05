import serial
import struct

serialData = serial.Serial("/dev/ttyACM0", 9600)
while True:
    byte: bytes = serialData.read(1)
    # print(byte[0])
    if (byte[0] & 0xA0) == 0x80:
        size = byte[0] & 0x1F
        # print(f"s- {size}")
        line: bytearray = serialData.read(size)
        if size == 3:
            btn, x, y = struct.unpack("Bbb", line)

            print(f"btn: {btn} - x: {x} - y: {y}\n", end='')
1000