cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c3dhall10 LANGUAGES MikroC)
else()
    project(lib_c3dhall10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c3dhall10 STATIC
        src/c3dhall10.c
        include/c3dhall10.h
)
add_library(Click.3DHall10  ALIAS lib_c3dhall10)

if (${MCU_NAME} MATCHES "(^PIC18F(.+)[KQ]4[23]$)|(^PIC32(.+)$)")
    set(sample_mode_reg_case "SAMPLE_REG_CASE_1")
else()
    set(sample_mode_reg_case "SAMPLE_REG_CASE_2")
endif()

target_compile_definitions(lib_c3dhall10 PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_c3dhall10 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c3dhall10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c3dhall10 PUBLIC MikroSDK.Driver)
