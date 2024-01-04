import serial
import struct

ZERO = 0
POS_SLOW = 1
POS_MEDIUM = 2
POS_FAST = 3
NEG_SLOW = 4
NEG_MEDIUM = 5
NEG_FAST = 6

def speed_str(v):
    if (v == ZERO):
        return "ZERO"
    elif (v == POS_SLOW):
        return "+1"
    elif (v == POS_MEDIUM):
        return "+2"
    elif (v == POS_FAST):
        return "+3"
    elif (v == NEG_SLOW):
        return "-1"
    elif (v == NEG_MEDIUM):
        return "-2"
    elif (v == NEG_FAST):
        return "-3"

serialData = serial.Serial("/dev/ttyACM0", 9600)
while True:
    byte: bytes = serialData.read(1)
    # print(byte[0])
    if byte[0] == 255:
        line: bytearray = serialData.read(3)
        btn, x, y = struct.unpack("<Bbb", line)
        x = speed_str(x)
        y = speed_str(y)

        print(f"btn: {btn} - x: {x} - y: {y}\n", end='')

        # if y < -100:
        #     buf = 1
        #     serialData.write(buf)
