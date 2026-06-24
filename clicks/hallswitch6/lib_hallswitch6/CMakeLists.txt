cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallswitch6 LANGUAGES MikroC)
else()
    project(lib_hallswitch6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallswitch6 STATIC
        src/hallswitch6.c
        include/hallswitch6.h
)
add_library(Click.HallSwitch6  ALIAS lib_hallswitch6)



target_include_directories(lib_hallswitch6 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallswitch6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallswitch6 PUBLIC MikroSDK.Driver)

