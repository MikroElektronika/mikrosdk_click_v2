cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_solidswitch LANGUAGES MikroC)
else()
    project(lib_solidswitch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_solidswitch STATIC
        src/solidswitch.c
        include/solidswitch.h
)
add_library(Click.SolidSwitch  ALIAS lib_solidswitch)



target_include_directories(lib_solidswitch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_solidswitch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_solidswitch PUBLIC MikroSDK.Driver)
