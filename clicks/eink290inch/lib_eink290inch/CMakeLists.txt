cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eink290inch LANGUAGES MikroC)
else()
    project(lib_eink290inch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eink290inch STATIC
        src/eink290inch.c
        include/eink290inch.h
        include/eink290inch_font.h
        include/eink290inch_image.h
)
add_library(Click.Eink290Inch  ALIAS lib_eink290inch)

if ((${MCU_NAME} MATCHES "(^PIC18F)") OR (${MCU_NAME} MATCHES "(^dsPIC)") OR (${MCU_NAME} MATCHES "(^ATMEGA)"))
	add_compile_definitions(IMAGE_MODE_ONLY)
endif()

target_include_directories(lib_eink290inch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eink290inch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eink290inch PUBLIC MikroSDK.Driver)
