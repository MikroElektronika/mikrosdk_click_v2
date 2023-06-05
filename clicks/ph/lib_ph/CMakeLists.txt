cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ph LANGUAGES MikroC)
else()
    project(lib_ph LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ph STATIC
        src/ph.c
        include/ph.h
)
add_library(Click.pH  ALIAS lib_ph)



target_include_directories(lib_ph PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ph PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ph PUBLIC MikroSDK.Driver)
