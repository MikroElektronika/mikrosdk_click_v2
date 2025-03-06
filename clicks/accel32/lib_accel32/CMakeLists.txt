cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accel32 LANGUAGES MikroC)
else()
    project(lib_accel32 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accel32 STATIC
        src/accel32.c
        include/accel32.h
)
add_library(Click.Accel32  ALIAS lib_accel32)

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

target_compile_definitions(lib_accel32 PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_accel32 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accel32 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accel32 PUBLIC MikroSDK.Driver)

