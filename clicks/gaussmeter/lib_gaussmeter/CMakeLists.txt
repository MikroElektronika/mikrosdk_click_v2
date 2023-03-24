cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gaussmeter LANGUAGES MikroC)
else()
    project(lib_gaussmeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gaussmeter STATIC
        src/gaussmeter.c
        include/gaussmeter.h
)
add_library(Click.Gaussmeter  ALIAS lib_gaussmeter)



target_include_directories(lib_gaussmeter PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gaussmeter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gaussmeter PUBLIC MikroSDK.Driver)
