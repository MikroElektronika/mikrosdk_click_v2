cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_opto LANGUAGES MikroC)
else()
    project(lib_opto LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_opto STATIC
        src/opto.c
        include/opto.h
)
add_library(Click.OPTO  ALIAS lib_opto)



target_include_directories(lib_opto PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_opto PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_opto PUBLIC MikroSDK.Driver)
