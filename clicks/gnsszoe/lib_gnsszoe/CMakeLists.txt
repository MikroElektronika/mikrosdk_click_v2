cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnsszoe LANGUAGES MikroC)
else()
    project(lib_gnsszoe LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnsszoe STATIC
        src/gnsszoe.c
        include/gnsszoe.h
)
add_library(Click.Gnsszoe  ALIAS lib_gnsszoe)

if (${MCU_NAME} MATCHES "(^PIC18F(.+)[KQ]4[23]$)|(^PIC32(.+)$)")
    set(sample_mode_reg_case "SAMPLE_REG_CASE_1")
else()
    set(sample_mode_reg_case "SAMPLE_REG_CASE_2")
endif()

target_compile_definitions(lib_gnsszoe PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_gnsszoe PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnsszoe PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnsszoe PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnsszoe PUBLIC MikroSDK.GenericPointer)
