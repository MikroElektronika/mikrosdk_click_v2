cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure2330ba LANGUAGES MikroC)
else()
    project(lib_pressure2330ba LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure2330ba STATIC
        src/pressure2330ba.c
        include/pressure2330ba.h
)
add_library(Click.Pressure2330BA  ALIAS lib_pressure2330ba)

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

target_compile_definitions(lib_pressure2330ba PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_pressure2330ba PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure2330ba PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure2330ba PUBLIC MikroSDK.Driver)

