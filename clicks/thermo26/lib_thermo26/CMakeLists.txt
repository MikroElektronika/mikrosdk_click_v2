cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo26 LANGUAGES MikroC)
else()
    project(lib_thermo26 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo26 STATIC
        src/thermo26.c
        include/thermo26.h
)
add_library(Click.Thermo26  ALIAS lib_thermo26)



target_include_directories(lib_thermo26 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo26 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo26 PUBLIC MikroSDK.Driver)
