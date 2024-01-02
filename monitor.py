import serial

serialData = serial.Serial("/dev/ttyACM0", 9600)
while True:
    line: str = serialData.readline().decode("utf-8")
    print(line, end='')
