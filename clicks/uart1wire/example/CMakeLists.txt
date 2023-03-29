cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_uart1wire LANGUAGES MikroC)
else()
    project(example_uart1wire LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_uart1wire
        main.c

)


############################ example_uart1wire GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_uart1wire PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_uart1wire PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_uart1wire PUBLIC MikroSDK.Log)
add_subdirectory(lib_uart1wire)
target_link_libraries(example_uart1wire PUBLIC Click.UART1Wire)
############################ example_uart1wire GENERATED CODE END ###########################
