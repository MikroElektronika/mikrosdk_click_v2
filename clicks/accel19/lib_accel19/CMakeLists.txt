cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accel19 LANGUAGES MikroC)
else()
    project(lib_accel19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accel19 STATIC
        src/accel19.c
        include/accel19.h
)
add_library(Click.Accel19  ALIAS lib_accel19)

if (${MCU_NAME} MATCHES "(^PIC18F(.+)[KQ]4[23]$)|(^PIC32(.+)$)")
    set(sample_mode_reg_case "SAMPLE_REG_CASE_1")
else()
    set(sample_mode_reg_case "SAMPLE_REG_CASE_2")
endif()

target_compile_definitions(lib_accel19 PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_accel19 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accel19 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accel19 PUBLIC MikroSDK.Driver)
