cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eth3 LANGUAGES MikroC)
else()
    project(lib_eth3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eth3 STATIC
        src/eth3.c
        include/eth3.h
)
add_library(Click.ETH3  ALIAS lib_eth3)

if (${CORE_NAME} MATCHES "DSPIC")
    if (${MCU_NAME} MATCHES "(^PIC24FV?(0[48]|16)K[ML][1234](.+)$)")
        set(sample_mode_reg_case "SAMPLE_REG_CASE_2")
    else()
        set(sample_mode_reg_case "SAMPLE_REG_CASE_1")
    endif()
else()
    if (${MCU_NAME} MATCHES "(^PIC18F(.+)[KQ]4[23]$)|(^PIC32(.+)$)")
        set(sample_mode_reg_case "SAMPLE_REG_CASE_1")
    else()
        set(sample_mode_reg_case "SAMPLE_REG_CASE_2")
    endif()
endif()

target_compile_definitions(lib_eth3 PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_eth3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eth3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eth3 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Ethernet.LAN9250 REQUIRED)
target_link_libraries(lib_eth3 PUBLIC MikroSDK.Ethernet.LAN9250)
find_package(MikroSDK.Ethernet.Net REQUIRED)
target_link_libraries(lib_eth3 PUBLIC MikroSDK.Ethernet.Net)

