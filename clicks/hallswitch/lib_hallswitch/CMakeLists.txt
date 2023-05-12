cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallswitch LANGUAGES MikroC)
else()
    project(lib_hallswitch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallswitch STATIC
        src/hallswitch.c
        include/hallswitch.h
)
add_library(Click.HallSwitch  ALIAS lib_hallswitch)



target_include_directories(lib_hallswitch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallswitch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallswitch PUBLIC MikroSDK.Driver)
