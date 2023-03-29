cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_force4 LANGUAGES MikroC)
else()
    project(lib_force4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_force4 STATIC
        src/force4.c
        include/force4.h
)
add_library(Click.Force4  ALIAS lib_force4)



target_include_directories(lib_force4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_force4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_force4 PUBLIC MikroSDK.Driver)
