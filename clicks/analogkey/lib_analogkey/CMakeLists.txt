cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_analogkey LANGUAGES MikroC)
else()
    project(lib_analogkey LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_analogkey STATIC
        src/analogkey.c
        include/analogkey.h
)
add_library(Click.AnalogKey  ALIAS lib_analogkey)



target_include_directories(lib_analogkey PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_analogkey PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_analogkey PUBLIC MikroSDK.Driver)
