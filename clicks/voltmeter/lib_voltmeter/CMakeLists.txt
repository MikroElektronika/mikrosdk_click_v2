cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_voltmeter LANGUAGES MikroC)
else()
    project(lib_voltmeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_voltmeter STATIC
        src/voltmeter.c
        include/voltmeter.h
)
add_library(Click.Voltmeter  ALIAS lib_voltmeter)



target_include_directories(lib_voltmeter PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_voltmeter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_voltmeter PUBLIC MikroSDK.Driver)
