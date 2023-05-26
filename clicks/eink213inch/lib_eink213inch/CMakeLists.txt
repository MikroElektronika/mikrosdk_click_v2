cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eink213inch LANGUAGES MikroC)
else()
    project(lib_eink213inch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eink213inch STATIC
        src/eink213inch.c
        include/eink213inch.h
        include/eink213inch_font.h
        include/eink213inch_image.h
)
add_library(Click.eInk213Inch  ALIAS lib_eink213inch)

if (${MCU_NAME} MATCHES "(^PIC18F)|(^ATMEGA)")
	add_compile_definitions(IMAGE_MODE_ONLY)
endif()

target_include_directories(lib_eink213inch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eink213inch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eink213inch PUBLIC MikroSDK.Driver)
