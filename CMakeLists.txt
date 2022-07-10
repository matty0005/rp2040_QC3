cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(rp2040-QC2)
pico_sdk_init()

add_executable(rp2040-QC2
        rp2040-QC2.c
        )

target_sources(rp2040-QC2 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/QC2.c
)

target_include_directories(rp2040-QC2 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/include
)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(rp2040-QC2 pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(rp2040-QC2)

#Enable USB serial 
pico_enable_stdio_usb(rp2040-QC2 1)
pico_enable_stdio_uart(rp2040-QC2 0)


