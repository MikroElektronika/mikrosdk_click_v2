cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lbandrtk LANGUAGES MikroC)
else()
    project(lib_lbandrtk LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lbandrtk STATIC
        src/lbandrtk.c
        include/lbandrtk.h
)
add_library(Click.LBANDRTK  ALIAS lib_lbandrtk)

if (${MCU_NAME} MATCHES "(^PIC18F(.+)[KQ]4[23]$)|(^PIC32(.+)$)")
    set(sample_mode_reg_case "SAMPLE_REG_CASE_1")
else()
    set(sample_mode_reg_case "SAMPLE_REG_CASE_2")
endif()

target_compile_definitions(lib_lbandrtk PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_lbandrtk PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lbandrtk PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lbandrtk PUBLIC MikroSDK.Driver)

