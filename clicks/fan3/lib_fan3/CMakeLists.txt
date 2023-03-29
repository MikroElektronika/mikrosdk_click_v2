cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_fan3 LANGUAGES MikroC)
else()
    project(lib_fan3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_fan3 STATIC
        src/fan3.c
        include/fan3.h
)
add_library(Click.Fan3  ALIAS lib_fan3)



target_include_directories(lib_fan3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_fan3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_fan3 PUBLIC MikroSDK.Driver)
