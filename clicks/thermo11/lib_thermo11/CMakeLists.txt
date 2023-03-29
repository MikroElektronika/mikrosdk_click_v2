cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo11 LANGUAGES MikroC)
else()
    project(lib_thermo11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo11 STATIC
        src/thermo11.c
        include/thermo11.h
)
add_library(Click.Thermo11  ALIAS lib_thermo11)



target_include_directories(lib_thermo11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo11 PUBLIC MikroSDK.Driver)
