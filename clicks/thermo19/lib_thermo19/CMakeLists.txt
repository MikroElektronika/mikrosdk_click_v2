cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo19 LANGUAGES MikroC)
else()
    project(lib_thermo19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo19 STATIC
        src/thermo19.c
        include/thermo19.h
)
add_library(Click.Thermo19  ALIAS lib_thermo19)



target_include_directories(lib_thermo19 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo19 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo19 PUBLIC MikroSDK.Driver)
