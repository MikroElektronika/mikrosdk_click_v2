cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo20 LANGUAGES MikroC)
else()
    project(lib_thermo20 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo20 STATIC
        src/thermo20.c
        include/thermo20.h
)
add_library(Click.Thermo20  ALIAS lib_thermo20)



target_include_directories(lib_thermo20 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo20 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo20 PUBLIC MikroSDK.Driver)
