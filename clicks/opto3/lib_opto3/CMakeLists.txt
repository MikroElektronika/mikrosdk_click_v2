cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_opto3 LANGUAGES MikroC)
else()
    project(lib_opto3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_opto3 STATIC
        src/opto3.c
        include/opto3.h
)
add_library(Click.Opto3  ALIAS lib_opto3)



target_include_directories(lib_opto3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_opto3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_opto3 PUBLIC MikroSDK.Driver)
