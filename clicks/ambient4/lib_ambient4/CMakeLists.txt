cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient4 LANGUAGES MikroC)
else()
    project(lib_ambient4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient4 STATIC
        src/ambient4.c
        include/ambient4.h
)
add_library(Click.Ambient4  ALIAS lib_ambient4)



target_include_directories(lib_ambient4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient4 PUBLIC MikroSDK.Driver)
