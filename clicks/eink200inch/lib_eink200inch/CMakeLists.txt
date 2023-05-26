cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eink200inch LANGUAGES MikroC)
else()
    project(lib_eink200inch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eink200inch STATIC
        src/eink200inch.c
        include/eink200inch.h
        include/eink200inch_font.h
        include/eink200inch_image.h
)
add_library(Click.Eink200Inch  ALIAS lib_eink200inch)

if (${MCU_NAME} MATCHES "(^PIC18F)")
	add_compile_definitions(IMAGE_MODE_ONLY)
endif()

target_include_directories(lib_eink200inch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eink200inch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eink200inch PUBLIC MikroSDK.Driver)
