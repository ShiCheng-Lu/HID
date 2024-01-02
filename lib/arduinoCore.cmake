add_library(Arduino STATIC
    lib/ArduinoCore-avr/cores/arduino/abi.cpp
    lib/ArduinoCore-avr/cores/arduino/CDC.cpp
    lib/ArduinoCore-avr/cores/arduino/HardwareSerial.cpp
    lib/ArduinoCore-avr/cores/arduino/HardwareSerial0.cpp
    lib/ArduinoCore-avr/cores/arduino/HardwareSerial1.cpp
    lib/ArduinoCore-avr/cores/arduino/HardwareSerial2.cpp
    lib/ArduinoCore-avr/cores/arduino/HardwareSerial3.cpp
    lib/ArduinoCore-avr/cores/arduino/hooks.c
    lib/ArduinoCore-avr/cores/arduino/IPAddress.cpp
    # lib/ArduinoCore-avr/cores/arduino/main.cpp
    lib/ArduinoCore-avr/cores/arduino/new.cpp
    lib/ArduinoCore-avr/cores/arduino/PluggableUSB.cpp
    lib/ArduinoCore-avr/cores/arduino/Print.cpp
    lib/ArduinoCore-avr/cores/arduino/Stream.cpp
    lib/ArduinoCore-avr/cores/arduino/Tone.cpp
    lib/ArduinoCore-avr/cores/arduino/USBCore.cpp
    lib/ArduinoCore-avr/cores/arduino/WInterrupts.c
    lib/ArduinoCore-avr/cores/arduino/wiring_analog.c
    lib/ArduinoCore-avr/cores/arduino/wiring_digital.c
    lib/ArduinoCore-avr/cores/arduino/wiring_pulse.c
    lib/ArduinoCore-avr/cores/arduino/wiring_pulse.S
    lib/ArduinoCore-avr/cores/arduino/wiring_shift.c
    lib/ArduinoCore-avr/cores/arduino/wiring.c
    lib/ArduinoCore-avr/cores/arduino/WMath.cpp
    lib/ArduinoCore-avr/cores/arduino/WString.cpp
)
target_compile_options(Arduino PUBLIC
    "-fno-exceptions"
    "-ffunction-sections"
    "-fdata-sections"
    "$<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>"
    "-mmcu=atmega328p"
    )
target_compile_definitions(Arduino PUBLIC
    "F_CPU=16000000L"
    "ARDUINO==10607"
    "ARDUINO_AVR_UNO"
    "ARDUINO_ARCH_AVR"
    )
target_link_options(Arduino PUBLIC
    "-mmcu=atmega328p"
    "-fuse-linker-plugin"
    "LINKER:--gc-sections"
    )
target_compile_features(Arduino PUBLIC 
    cxx_std_11 c_std_11)
target_include_directories(Arduino PUBLIC 
    lib/ArduinoCore-avr/cores/arduino 
    lib/ArduinoCore-avr/variants/standard)

