cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_solenoiddriver LANGUAGES MikroC)
else()
    project(lib_solenoiddriver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_solenoiddriver STATIC
        src/solenoiddriver.c
        include/solenoiddriver.h
)
add_library(Click.SolenoidDriver  ALIAS lib_solenoiddriver)

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

target_compile_definitions(lib_solenoiddriver PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_solenoiddriver PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_solenoiddriver PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_solenoiddriver PUBLIC MikroSDK.Driver)

