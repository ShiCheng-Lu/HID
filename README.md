# Echo-HID


HID device that can be controlled by sending Keyboard/Mouse reports to the device.
In addition, a button enables Joystick control via Atmega328p (Arduino UNO Rev3).

Atmega16u2 as USB controller
Atmega328p as peripheral controller

HID library that Generates USD + HID descriptors from definition with some slightly cursed C macros.

## Dev notes

Attaching USB device to WSL
```
usbipd list
usbipd bind -b <busid>
usbipd attach --wsl --busid <busid>
usbipd detach --busid <busid>
```

Building and flashing device firmware
```
sudo apt-get update
sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr avrdude dfu-programmer

cmake -S . -B build
cmake --build build

cmake --build build -t flash_peripheral
cmake --build build -t flash_usb_interface

// reset atmega16u2 firmware back to original Arduino usbserial firmware
sudo dfu-programmer atmega16u2 flash Arduino-usbserial-atmega16u2-Uno-Rev3.hex
```
