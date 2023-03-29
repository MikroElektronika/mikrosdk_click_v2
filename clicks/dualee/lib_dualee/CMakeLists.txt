cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dualee LANGUAGES MikroC)
else()
    project(lib_dualee LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dualee STATIC
        src/dualee.c
        include/dualee.h
)
add_library(Click.DualEE  ALIAS lib_dualee)



target_include_directories(lib_dualee PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dualee PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dualee PUBLIC MikroSDK.Driver)
