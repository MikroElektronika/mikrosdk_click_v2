cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity18 LANGUAGES MikroC)
else()
    project(lib_proximity18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity18 STATIC
        src/proximity18.c
        include/proximity18.h
)
add_library(Click.Proximity18  ALIAS lib_proximity18)



target_include_directories(lib_proximity18 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity18 PUBLIC MikroSDK.Driver)
