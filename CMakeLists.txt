cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(uros_pico_example C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

link_directories(libmicroros)
add_executable(uros_pico_example
    # pico_uros_wifi_example.c
    # pico_wifi_transport.c
    pico_micro_ros_example.c
    pico_uart_transport.c
)

# target_compile_definitions(uros_pico_example PRIVATE
#         WIFI_SSID=\"${WIFI_SSID}\"
#         WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
#         )

target_link_libraries(uros_pico_example
    pico_stdlib
    microros
    # pico_cyw43_arch_lwip_threadsafe_background
)

target_include_directories(uros_pico_example PUBLIC
    libmicroros/include
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/..
)

SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

# Configure Pico
pico_enable_stdio_usb(uros_pico_example 1)
pico_enable_stdio_uart(uros_pico_example 0)
add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# Generate UF2
pico_add_extra_outputs(uros_pico_example)

# if (PICO_CYW43_SUPPORTED) # set by PICO_BOARD=pico_w
#     if (NOT TARGET pico_cyw43_arch)
#         message("Skipping Pico W examples as support is not available")
#     else()
#         message("+Creating Pico W projects")
#         if (DEFINED ENV{WIFI_SSID} AND (NOT WIFI_SSID))
#             set(WIFI_SSID $ENV{WIFI_SSID})
#             message("Using WIFI_SSID from environment ('${WIFI_SSID}')")
#         endif()

#         if (DEFINED ENV{WIFI_PASSWORD} AND (NOT WIFI_PASSWORD))
#             set(WIFI_PASSWORD $ENV{WIFI_PASSWORD})
#             message("Using WIFI_PASSWORD from environment")
#         endif()

#         set(WIFI_SSID "${WIFI_SSID}" CACHE INTERNAL "WiFi SSID for examples")
#         set(WIFI_PASSWORD "${WIFI_PASSWORD}" CACHE INTERNAL "WiFi password for examples")

#     endif()
# else()
#     message("*** PICO_CYW43_SUPPORTED not set, skipping Pico W projects")
# endif()
