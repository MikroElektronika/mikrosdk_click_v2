cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity8 LANGUAGES MikroC)
else()
    project(lib_proximity8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity8 STATIC
        src/proximity8.c
        include/proximity8.h
)
add_library(Click.Proximity8  ALIAS lib_proximity8)



target_include_directories(lib_proximity8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity8 PUBLIC MikroSDK.Driver)
