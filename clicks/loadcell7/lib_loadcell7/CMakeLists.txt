cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_loadcell7 LANGUAGES MikroC)
else()
    project(lib_loadcell7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_loadcell7 STATIC
        src/loadcell7.c
        include/loadcell7.h
)
add_library(Click.LoadCell7  ALIAS lib_loadcell7)

if (${MCU_NAME} MATCHES "(^PIC18F(.+)[KQ]4[23]$)|(^PIC32(.+)$)")
    set(sample_mode_reg_case "SAMPLE_REG_CASE_1")
else()
    set(sample_mode_reg_case "SAMPLE_REG_CASE_2")
endif()

target_compile_definitions(lib_loadcell7 PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_loadcell7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_loadcell7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_loadcell7 PUBLIC MikroSDK.Driver)
