cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c4glte2voice LANGUAGES MikroC)
else()
    project(lib_c4glte2voice LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c4glte2voice STATIC
        src/c4glte2voice.c
        include/c4glte2voice.h
)
add_library(Click.4GLTE2Voice  ALIAS lib_c4glte2voice)



target_include_directories(lib_c4glte2voice PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c4glte2voice PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c4glte2voice PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c4glte2voice PUBLIC MikroSDK.Conversions)
