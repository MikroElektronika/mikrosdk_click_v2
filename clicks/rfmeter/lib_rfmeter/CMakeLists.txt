cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rfmeter LANGUAGES MikroC)
else()
    project(lib_rfmeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rfmeter STATIC
        src/rfmeter.c
        include/rfmeter.h
)
add_library(Click.RfMeter  ALIAS lib_rfmeter)



target_include_directories(lib_rfmeter PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rfmeter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rfmeter PUBLIC MikroSDK.Driver)
