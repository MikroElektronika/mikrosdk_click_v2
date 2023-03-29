cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mic23099 LANGUAGES MikroC)
else()
    project(lib_mic23099 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mic23099 STATIC
        src/mic23099.c
        include/mic23099.h
)
add_library(Click.Mic23099  ALIAS lib_mic23099)



target_include_directories(lib_mic23099 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mic23099 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mic23099 PUBLIC MikroSDK.Driver)
