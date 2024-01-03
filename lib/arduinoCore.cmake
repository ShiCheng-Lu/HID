set(ArduinoCorePath lib/ArduinoCore-avr)

add_library(Arduino STATIC
    ${ArduinoCorePath}/cores/arduino/abi.cpp
    ${ArduinoCorePath}/cores/arduino/CDC.cpp
    ${ArduinoCorePath}/cores/arduino/HardwareSerial.cpp
    ${ArduinoCorePath}/cores/arduino/HardwareSerial0.cpp
    ${ArduinoCorePath}/cores/arduino/HardwareSerial1.cpp
    ${ArduinoCorePath}/cores/arduino/HardwareSerial2.cpp
    ${ArduinoCorePath}/cores/arduino/HardwareSerial3.cpp
    ${ArduinoCorePath}/cores/arduino/hooks.c
    ${ArduinoCorePath}/cores/arduino/IPAddress.cpp
    # ${ArduinoCorePath}/cores/arduino/main.cpp
    ${ArduinoCorePath}/cores/arduino/new.cpp
    ${ArduinoCorePath}/cores/arduino/PluggableUSB.cpp
    ${ArduinoCorePath}/cores/arduino/Print.cpp
    ${ArduinoCorePath}/cores/arduino/Stream.cpp
    ${ArduinoCorePath}/cores/arduino/Tone.cpp
    ${ArduinoCorePath}/cores/arduino/USBCore.cpp
    ${ArduinoCorePath}/cores/arduino/WInterrupts.c
    ${ArduinoCorePath}/cores/arduino/wiring_analog.c
    ${ArduinoCorePath}/cores/arduino/wiring_digital.c
    ${ArduinoCorePath}/cores/arduino/wiring_pulse.c
    ${ArduinoCorePath}/cores/arduino/wiring_pulse.S
    ${ArduinoCorePath}/cores/arduino/wiring_shift.c
    ${ArduinoCorePath}/cores/arduino/wiring.c
    ${ArduinoCorePath}/cores/arduino/WMath.cpp
    ${ArduinoCorePath}/cores/arduino/WString.cpp
)
target_compile_options(Arduino PUBLIC
    "-fno-exceptions"
    "-ffunction-sections"
    "-fdata-sections"
    "$<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>"
    "-mmcu=${MCU}"
    )
target_compile_definitions(Arduino PUBLIC
    "F_CPU=16000000L"
    "ARDUINO==10607"
    "ARDUINO_AVR_UNO"
    "ARDUINO_ARCH_AVR"
    "USB_VID=1"
    "USB_PID=1"
    )
target_link_options(Arduino PUBLIC
    "-mmcu=${MCU}"
    "-fuse-linker-plugin"
    "LINKER:--gc-sections"
    )
target_compile_features(Arduino PUBLIC 
    cxx_std_11 c_std_11)
target_include_directories(Arduino PUBLIC 
    ${ArduinoCorePath}/cores/arduino
    ${ArduinoCorePath}/variants/standard)

