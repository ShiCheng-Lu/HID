set(MCU atmega16u2)

set(target usb_interface)

add_executable(${target}
    src/main.c
    src/Descriptors.c
    src/UsbEvents.c
    src/SerialInterface.c
    )

target_link_libraries(${target} PRIVATE LUFA_${MCU})
target_link_libraries(${target} PRIVATE HID)
target_include_directories(${target} PRIVATE inc)

# generate .hex file
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
    flash_${target}
    COMMAND sudo dfu-programmer atmega16u2 flash ${target}.hex
    COMMENT "flash hex")
add_dependencies(flash_${target} ${target})
