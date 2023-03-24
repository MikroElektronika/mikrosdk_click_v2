cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_remotetemp LANGUAGES MikroC)
else()
    project(lib_remotetemp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_remotetemp STATIC
        src/remotetemp.c
        include/remotetemp.h
)
add_library(Click.RemoteTemp  ALIAS lib_remotetemp)



target_include_directories(lib_remotetemp PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_remotetemp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_remotetemp PUBLIC MikroSDK.Driver)
