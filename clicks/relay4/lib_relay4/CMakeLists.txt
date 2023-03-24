cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_relay4 LANGUAGES MikroC)
else()
    project(lib_relay4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_relay4 STATIC
        src/relay4.c
        include/relay4.h
)
add_library(Click.Relay4  ALIAS lib_relay4)



target_include_directories(lib_relay4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_relay4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_relay4 PUBLIC MikroSDK.Driver)

