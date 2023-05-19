cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_earthquake LANGUAGES MikroC)
else()
    project(lib_earthquake LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_earthquake STATIC
        src/earthquake.c
        include/earthquake.h
)
add_library(Click.Earthquake  ALIAS lib_earthquake)



target_include_directories(lib_earthquake PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_earthquake PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_earthquake PUBLIC MikroSDK.Driver)
