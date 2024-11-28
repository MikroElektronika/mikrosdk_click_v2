cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_piezoaccel250g LANGUAGES MikroC)
else()
    project(lib_piezoaccel250g LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_piezoaccel250g STATIC
        src/piezoaccel250g.c
        include/piezoaccel250g.h
)
add_library(Click.PiezoAccel250g  ALIAS lib_piezoaccel250g)

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

target_compile_definitions(lib_piezoaccel250g PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_piezoaccel250g PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_piezoaccel250g PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_piezoaccel250g PUBLIC MikroSDK.Driver)

