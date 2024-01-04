set(LUFA_REPO_PATH ${PROJECT_SOURCE_DIR}/lib/lufa)
set(LUFA_ROOT_PATH ${LUFA_REPO_PATH}/LUFA)
set(ARCH AVR8)

add_library(LUFA_${MCU} STATIC
    # inc/LUFAConfig.h
    # LUFA_SRC_USB_COMMON
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/USBController_${ARCH}.c
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/USBInterrupt_${ARCH}.c 
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/ConfigDescriptors.c            
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/Events.c                       
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/USBTask.c                      
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Common/HIDParser.c            
    # LUFA_SRC_USB_HOST
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/Host_${ARCH}.c       
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/Pipe_${ARCH}.c       
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/PipeStream_${ARCH}.c 
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/HostStandardReq.c
    # LUFA_SRC_USB_DEVICE
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/Device_${ARCH}.c         
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/Endpoint_${ARCH}.c       
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/EndpointStream_${ARCH}.c 
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/DeviceStandardReq.c
    # LUFA_SRC_USBCLASS_DEVICE
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/AudioClassDevice.c       
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/CCIDClassDevice.c        
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/CDCClassDevice.c         
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/HIDClassDevice.c         
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/MassStorageClassDevice.c 
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/MIDIClassDevice.c        
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/PrinterClassDevice.c     
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/RNDISClassDevice.c
    # LUFA_SRC_USBCLASS_HOST
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/AndroidAccessoryClassHost.c
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/AudioClassHost.c           
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/CDCClassHost.c             
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/HIDClassHost.c             
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/MassStorageClassHost.c     
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/MIDIClassHost.c            
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/PrinterClassHost.c         
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/RNDISClassHost.c           
    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/StillImageClassHost.c
    # LUFA_SRC_TEMPERATURE
    ${LUFA_ROOT_PATH}/Drivers/Board/Temperature.c
    # LUFA_SRC_SERIAL
    ${LUFA_ROOT_PATH}/Drivers/Peripheral/${ARCH}/Serial_${ARCH}.c
    # LUFA_SRC_TWI
    ${LUFA_ROOT_PATH}/Drivers/Peripheral/${ARCH}/TWI_${ARCH}.c)

target_include_directories(LUFA_${MCU} PUBLIC
    ${LUFA_ROOT_PATH}/Drivers/USB/Core
    ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}
    ${LUFA_ROOT_PATH}/Drivers/USB
    ${LUFA_REPO_PATH}
    )

target_compile_options(LUFA_${MCU} PUBLIC
    "-funsigned-char"
    "-funsigned-bitfields"
    "-ffunction-sections"
    "-fno-inline-small-functions"
    "-fpack-struct"
    "-fshort-enums"
    "-fno-strict-aliasing"
    "-Wall"
    "-Wstrict-prototypes"
    "-mmcu=${MCU}"
    )
target_compile_definitions(LUFA_${MCU} PUBLIC
    "F_CPU=16000000L"
    "F_USB=16000000L"
    "F_CLOCK=16000000L"
    "ARCH=${ARCH}"
    "INTERRUPT_CONTROL_ENDPOINT"
    "DEVICE_STATE_AS_GPIOR=0"
    "AVR_RESET_LINE_PORT=PORTD"
    "AVR_RESET_LINE_DDR=DDRD"
    "AVR_RESET_LINE_MASK=(1 << 7)"
    )
target_compile_definitions(LUFA_${MCU} PUBLIC
    "USB_DEVICE_ONLY"
    "USE_FLASH_DESCRIPTORS"
    "USE_STATIC_OPTIONS=(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)"
    "FIXED_CONTROL_ENDPOINT_SIZE=8"
    "FIXED_NUM_CONFIGURATIONS=1"
    )
target_link_options(LUFA_${MCU} PUBLIC
    "-mmcu=${MCU}"
    "-fuse-linker-plugin"
    "LINKER:--gc-sections"
    )
target_compile_features(LUFA_${MCU} PUBLIC 
    cxx_std_11 c_std_11)
