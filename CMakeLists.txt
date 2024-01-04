
cmake_minimum_required(VERSION 3.19)

set(CMAKE_C_COMPILER   avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

add_compile_options(-Os)

project(
    Echo-HID
    VERSION 1.0
    LANGUAGES C CXX ASM)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MCU atmega328p)
include(lib/arduinoCore.cmake)
set(MCU atmega16u2)
include(lib/lufa.cmake)
include(lib/hid.cmake)

set(MCU)

add_subdirectory(usb_interface)
add_subdirectory(peripheral)
