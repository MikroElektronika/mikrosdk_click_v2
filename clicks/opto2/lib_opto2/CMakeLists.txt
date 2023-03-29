cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_opto2 LANGUAGES MikroC)
else()
    project(lib_opto2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_opto2 STATIC
        src/opto2.c
        include/opto2.h
)
add_library(Click.Opto2  ALIAS lib_opto2)



target_include_directories(lib_opto2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_opto2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_opto2 PUBLIC MikroSDK.Driver)
