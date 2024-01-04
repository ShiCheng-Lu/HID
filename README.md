
Generates USD + HID descriptors from definition with some slightly cursed C macros.

Hopefully will become a HID keyboard and mouse commandable device that will allow keyboard/mouse inputs from USB.

https://github.com/MicrosoftDocs/WSL/issues/1868

```
usbipd list
usbipd bind -b <busid>
usbipd attach --wsl --busid <busid>
usbipd detach --busid <busid>
```

```
sudo apt-get update
sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr avrdude

cmake -S . -B build
cmake --build build
```
