cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure19 LANGUAGES MikroC)
else()
    project(lib_pressure19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure19 STATIC
        src/pressure19.c
        include/pressure19.h
)
add_library(Click.Pressure19  ALIAS lib_pressure19)



target_include_directories(lib_pressure19 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure19 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure19 PUBLIC MikroSDK.Driver)
