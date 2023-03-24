cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity LANGUAGES MikroC)
else()
    project(lib_proximity LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity STATIC
        src/proximity.c
        include/proximity.h
)
add_library(Click.Proximity  ALIAS lib_proximity)



target_include_directories(lib_proximity PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity PUBLIC MikroSDK.Driver)
