cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo16 LANGUAGES MikroC)
else()
    project(lib_thermo16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo16 STATIC
        src/thermo16.c
        include/thermo16.h
)
add_library(Click.Thermo16  ALIAS lib_thermo16)



target_include_directories(lib_thermo16 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo16 PUBLIC MikroSDK.Driver)
