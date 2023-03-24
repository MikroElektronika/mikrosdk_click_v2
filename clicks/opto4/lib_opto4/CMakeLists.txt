cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_opto4 LANGUAGES MikroC)
else()
    project(lib_opto4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_opto4 STATIC
        src/opto4.c
        include/opto4.h
)
add_library(Click.OPTO4  ALIAS lib_opto4)



target_include_directories(lib_opto4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_opto4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_opto4 PUBLIC MikroSDK.Driver)
