cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity17 LANGUAGES MikroC)
else()
    project(lib_proximity17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity17 STATIC
        src/proximity17.c
        include/proximity17.h
)
add_library(Click.Proximity17  ALIAS lib_proximity17)



target_include_directories(lib_proximity17 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity17 PUBLIC MikroSDK.Driver)
