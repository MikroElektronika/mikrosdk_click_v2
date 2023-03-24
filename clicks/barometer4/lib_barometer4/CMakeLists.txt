cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_barometer4 LANGUAGES MikroC)
else()
    project(lib_barometer4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_barometer4 STATIC
        src/barometer4.c
        include/barometer4.h
)
add_library(Click.Barometer4  ALIAS lib_barometer4)



target_include_directories(lib_barometer4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_barometer4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_barometer4 PUBLIC MikroSDK.Driver)
