
Generates USD + HID descriptors from definition with some slightly cursed C macros.

Hopefully will become a HID keyboard and mouse commandable device that will allow keyboard/mouse inputs from USB.

https://github.com/MicrosoftDocs/WSL/issues/1868

```
usbipd list
usbipd bind -b <busid>
usbipd attach --wsl --busid <busid>

```

```
Using board 'uno' from platform in folder: C:\Users\shich\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6
Using core 'arduino' from platform in folder: C:\Users\shich\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6
Detecting libraries used...
"C:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -flto -w -x c++ -E -CC -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10607 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR "-IC:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\avr\\1.8.6\\cores\\arduino" "-IC:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\avr\\1.8.6\\variants\\standard" "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87\\sketch\\sketch_dec31a.ino.cpp" -o nul

Generating function prototypes...
"C:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -flto -w -x c++ -E -CC -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10607 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR "-IC:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\avr\\1.8.6\\cores\\arduino" "-IC:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\avr\\1.8.6\\variants\\standard" "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87\\sketch\\sketch_dec31a.ino.cpp" -o "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87\\preproc\\ctags_target_for_gcc_minus_e.cpp"

"C:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\builtin\\tools\\ctags\\5.8-arduino11/ctags" -u --language-force=c++ -f - --c++-kinds=svpf --fields=KSTtzns --line-directives "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87\\preproc\\ctags_target_for_gcc_minus_e.cpp"

Compiling sketch...

"C:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10607 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR "-IC:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\avr\\1.8.6\\cores\\arduino" "-IC:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\avr\\1.8.6\\variants\\standard" "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87\\sketch\\sketch_dec31a.ino.cpp" -o "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87\\sketch\\sketch_dec31a.ino.cpp.o"

Compiling libraries...
Compiling core...
Using precompiled core: C:\Users\shich\AppData\Local\Temp\arduino-core-cache\core_arduino_avr_uno_a226f3b8758e99f6b171bf787dd9a401.a
Linking everything together...

"C:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7/bin/avr-gcc" -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -o "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87/sketch_dec31a.ino.elf" "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87\\sketch\\sketch_dec31a.ino.cpp.o" "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87/..\\arduino-core-cache\\core_arduino_avr_uno_a226f3b8758e99f6b171bf787dd9a401.a" "-LC:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87" -lm
    avr-gcc -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -o <file.elf>

"C:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87/sketch_dec31a.ino.elf" "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87/sketch_dec31a.ino.eep"
    avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 <file.elf> <file.eep>

"C:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7/bin/avr-objcopy" -O ihex -R .eeprom "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87/sketch_dec31a.ino.elf" "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87/sketch_dec31a.ino.hex"
    avr-objcopy -O ihex -R .eeprom <file.elf> <file.hex>

"C:\\Users\\shich\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7/bin/avr-size" -A "C:\\Users\\shich\\AppData\\Local\\Temp\\arduino-sketch-2154426AAFBE100985971692A31CFD87/sketch_dec31a.ino.elf"
    avr-size -A <file.elf>

Sketch uses 444 bytes (1%) of program storage space. Maximum is 32256 bytes.
Global variables use 9 bytes (0%) of dynamic memory, leaving 2039 bytes for local variables. Maximum is 2048 bytes.

"C:\Users\shich\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude" "-CC:\Users\shich\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf" -v -V -patmega328p -carduino "-PCOM3" -b115200 -D "-Uflash:w:C:\Users\shich\AppData\Local\Temp\arduino-sketch-2154426AAFBE100985971692A31CFD87/sketch_dec31a.ino.hex:i"
    
    avrdude ... -v -V -patmega328p -carduino -PCOM? -b115200 -D <file.hex>:i

```