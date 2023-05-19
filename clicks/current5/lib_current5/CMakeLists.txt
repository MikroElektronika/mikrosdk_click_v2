cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current5 LANGUAGES MikroC)
else()
    project(lib_current5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current5 STATIC
        src/current5.c
        include/current5.h
)
add_library(Click.Current5  ALIAS lib_current5)

if (${MCU_NAME} MATCHES "(^PIC18F(.+)[KQ]4[23]$)|(^PIC32(.+)$)")
    set(sample_mode_reg_case "SAMPLE_REG_CASE_1")
else()
    set(sample_mode_reg_case "SAMPLE_REG_CASE_2")
endif()

target_compile_definitions(lib_current5 PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_current5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current5 PUBLIC MikroSDK.Driver)
