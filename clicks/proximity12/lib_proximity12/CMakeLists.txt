cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity12 LANGUAGES MikroC)
else()
    project(lib_proximity12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity12 STATIC
        src/proximity12.c
        include/proximity12.h
)
add_library(Click.Proximity12  ALIAS lib_proximity12)



target_include_directories(lib_proximity12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity12 PUBLIC MikroSDK.Driver)
