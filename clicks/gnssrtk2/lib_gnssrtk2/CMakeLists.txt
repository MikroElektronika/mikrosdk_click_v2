cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnssrtk2 LANGUAGES MikroC)
else()
    project(lib_gnssrtk2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnssrtk2 STATIC
        src/gnssrtk2.c
        include/gnssrtk2.h
)
add_library(Click.GNSSRTK2  ALIAS lib_gnssrtk2)

if (${MCU_NAME} MATCHES "(^PIC18F(.+)[KQ]4[23]$)|(^PIC32(.+)$)")
    set(sample_mode_reg_case "SAMPLE_REG_CASE_1")
else()
    set(sample_mode_reg_case "SAMPLE_REG_CASE_2")
endif()

target_compile_definitions(lib_gnssrtk2 PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_gnssrtk2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnssrtk2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnssrtk2 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnssrtk2 PUBLIC MikroSDK.GenericPointer)
