cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_airquality13 LANGUAGES MikroC)
else()
    project(lib_airquality13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_airquality13 STATIC
        src/airquality13.c
        include/airquality13.h
)
add_library(Click.AirQuality13  ALIAS lib_airquality13)

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

target_compile_definitions(lib_airquality13 PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_airquality13 PUBLIC 
        include
)

# Bosch BMV080 SDK integration
target_include_directories(lib_airquality13 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/bosch/inc
)
if (${CORE_NAME} MATCHES "M4EF")
    set(BOSCH_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bosch/lib/arm_cortex_m4f")

elseif (${CORE_NAME} MATCHES "M7")
    set(BOSCH_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bosch/lib/arm_cortex_m7f")

elseif (${CORE_NAME} MATCHES "M33EF")
    set(BOSCH_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bosch/lib/arm_cortex_m33f")

elseif (${CORE_NAME} MATCHES "M33")
    set(BOSCH_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bosch/lib/arm_cortex_m33")

elseif (${CORE_NAME} MATCHES "M4")
    set(BOSCH_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bosch/lib/arm_cortex_m4")

elseif (${CORE_NAME} MATCHES "M0")
    set(BOSCH_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bosch/lib/arm_cortex_m0plus")

elseif (${CORE_NAME} MATCHES "RISCV")
    set(BOSCH_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bosch/lib/riscv_rv32imc")

elseif (${CORE_NAME} MATCHES "^(P18|DSPIC|MIPS32|MICROAPTIV|GT64K|LTE64K)$")
    message(FATAL_ERROR
        "Air Quality 13 Click: MCU core '${CORE_NAME}' (${MCU_NAME}) is not supported.\n"
        "The Bosch BMV080 SDK does not provide pre-compiled libraries for PIC18, "
        "dsPIC33, PIC32 (MIPS), or ATmega (AVR) architectures.\n"
        "Supported cores: ARM Cortex-M0+, M4, M4F, M33, M33F, M7F and RISC-V RV32IMC."
    )
else()
    message(FATAL_ERROR
        "Air Quality 13 Click: Unknown or unsupported MCU core '${CORE_NAME}' (${MCU_NAME}).\n"
        "Supported cores: M0, M4, M4EF, M33, M33EF, M7, RISCV."
    )
endif()

add_library(lib_bmv080 STATIC IMPORTED)
set_target_properties(lib_bmv080 PROPERTIES
    IMPORTED_LOCATION ${BOSCH_LIB_DIR}/lib_bmv080.a
)

add_library(lib_postProcessor STATIC IMPORTED)
set_target_properties(lib_postProcessor PROPERTIES
    IMPORTED_LOCATION ${BOSCH_LIB_DIR}/lib_postProcessor.a
)

target_link_libraries(lib_airquality13 PUBLIC lib_bmv080 lib_postProcessor m)
find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_airquality13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_airquality13 PUBLIC MikroSDK.Driver)

