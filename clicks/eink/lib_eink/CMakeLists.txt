cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eink LANGUAGES MikroC)
else()
    project(lib_eink LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eink STATIC
        src/eink.c
        include/eink.h
        include/eink200inch_font.h
        include/eink200inch_image.h
)
add_library(Click.Eink  ALIAS lib_eink)

if ((${MCU_NAME} MATCHES "(^PIC18F)") OR (${MCU_NAME} MATCHES "(^dsPIC)") OR (${MCU_NAME} MATCHES "(^ATMEGA)"))
	add_compile_definitions(IMAGE_MODE_ONLY)
endif()

target_include_directories(lib_eink PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eink PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eink PUBLIC MikroSDK.Driver)
