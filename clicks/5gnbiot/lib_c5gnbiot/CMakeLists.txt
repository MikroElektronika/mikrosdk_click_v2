cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c5gnbiot LANGUAGES MikroC)
else()
    project(lib_c5gnbiot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c5gnbiot STATIC
        src/c5gnbiot.c
        include/c5gnbiot.h
)
add_library(Click.5gNbIot  ALIAS lib_c5gnbiot)



target_include_directories(lib_c5gnbiot PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c5gnbiot PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c5gnbiot PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c5gnbiot PUBLIC MikroSDK.Conversions)
