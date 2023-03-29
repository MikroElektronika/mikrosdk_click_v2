cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hvac LANGUAGES MikroC)
else()
    project(lib_hvac LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hvac STATIC
        src/hvac.c
        include/hvac.h
)
add_library(Click.Hvac  ALIAS lib_hvac)



target_include_directories(lib_hvac PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hvac PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hvac PUBLIC MikroSDK.Driver)
