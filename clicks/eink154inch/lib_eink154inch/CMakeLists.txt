cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eink154inch LANGUAGES MikroC)
else()
    project(lib_eink154inch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eink154inch STATIC
        src/eink154inch.c
        include/eink154inch.h
        include/eink154inch_font.h
        include/eink154inch_image.h
)
add_library(Click.Eink154Inch  ALIAS lib_eink154inch)

if (${MCU_NAME} MATCHES "(^PIC18F)|(^ATMEGA)")
	add_compile_definitions(IMAGE_MODE_ONLY)
endif()

target_include_directories(lib_eink154inch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eink154inch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eink154inch PUBLIC MikroSDK.Driver)
