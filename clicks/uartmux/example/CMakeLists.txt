cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_uartmux LANGUAGES MikroC)
else()
    project(example_uartmux LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_uartmux
        main.c

)


############################ example_uartmux GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_uartmux PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_uartmux PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_uartmux PUBLIC MikroSDK.Log)
add_subdirectory(lib_uartmux)
target_link_libraries(example_uartmux PUBLIC Click.UartMux)
############################ example_uartmux GENERATED CODE END ###########################
