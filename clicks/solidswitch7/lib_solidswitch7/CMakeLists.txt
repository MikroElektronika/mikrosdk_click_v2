cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_solidswitch7 LANGUAGES MikroC)
else()
    project(lib_solidswitch7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_solidswitch7 STATIC
        src/solidswitch7.c
        include/solidswitch7.h
)
add_library(Click.SolidSwitch7  ALIAS lib_solidswitch7)



target_include_directories(lib_solidswitch7 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_solidswitch7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_solidswitch7 PUBLIC MikroSDK.Driver)

