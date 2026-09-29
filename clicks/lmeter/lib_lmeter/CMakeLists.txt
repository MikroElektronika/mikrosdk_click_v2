cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lmeter LANGUAGES MikroC)
else()
    project(lib_lmeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lmeter STATIC
        src/lmeter.c
        include/lmeter.h
)
add_library(Click.Lmeter  ALIAS lib_lmeter)



target_include_directories(lib_lmeter PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lmeter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lmeter PUBLIC MikroSDK.Driver)

