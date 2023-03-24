cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dht22 LANGUAGES MikroC)
else()
    project(lib_dht22 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dht22 STATIC
        src/dht22.c
        include/dht22.h
)
add_library(Click.Dht22  ALIAS lib_dht22)



target_include_directories(lib_dht22 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dht22 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dht22 PUBLIC MikroSDK.Driver)
