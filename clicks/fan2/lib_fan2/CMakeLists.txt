cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_fan2 LANGUAGES MikroC)
else()
    project(lib_fan2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_fan2 STATIC
        src/fan2.c
        include/fan2.h
)
add_library(Click.Fan2  ALIAS lib_fan2)



target_include_directories(lib_fan2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_fan2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_fan2 PUBLIC MikroSDK.Driver)
