cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_solidswitch10 LANGUAGES MikroC)
else()
    project(lib_solidswitch10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_solidswitch10 STATIC
        src/solidswitch10.c
        include/solidswitch10.h
)
add_library(Click.SolidSwitch10  ALIAS lib_solidswitch10)



target_include_directories(lib_solidswitch10 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_solidswitch10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_solidswitch10 PUBLIC MikroSDK.Driver)

