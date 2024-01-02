
cmake_minimum_required(VERSION 3.19)

set(CMAKE_C_COMPILER   avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

set(target main)

project(
    Echo-HID
    VERSION 1.0
    LANGUAGES C CXX ASM)

include(lib/arduinoCore.cmake)

add_library(USB lib/usb/usb_descriptors.cpp lib/usb/usb_descriptors.h)
target_include_directories(USB PUBLIC lib)

add_executable(${target} src/main.cpp)
target_link_libraries(${target} PRIVATE Arduino)

# generate .hex file
# set_target_properties(${target} PROPERTIES SUFFIX ".elf")
add_custom_command(
    TARGET ${target} POST_BUILD
    BYPRODUCTS ${target}.hex
    COMMAND ${CMAKE_OBJCOPY} -O ihex -j .eeprom 
        --set-section-flags=.eeprom=alloc,load 
        --no-change-warnings 
        --change-section-lma 
        .eeprom=0 
        ${target} ${target}.eep)
add_custom_command(
    TARGET ${target} POST_BUILD
    BYPRODUCTS ${target}.hex
    ${target}.hex
    COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom 
    ${target} ${target}.hex)

add_custom_target(
    flash 
    COMMAND sudo avrdude -v -V -patmega328p -carduino -P/dev/ttyACM0 -D -U flash:w:${target}.hex:i
    COMMENT "flash hex")
add_dependencies(flash ${target})
