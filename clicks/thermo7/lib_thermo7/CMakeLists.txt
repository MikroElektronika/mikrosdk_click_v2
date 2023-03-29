cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo7 LANGUAGES MikroC)
else()
    project(lib_thermo7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo7 STATIC
        src/thermo7.c
        include/thermo7.h
)
add_library(Click.Thermo7  ALIAS lib_thermo7)



target_include_directories(lib_thermo7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo7 PUBLIC MikroSDK.Driver)
