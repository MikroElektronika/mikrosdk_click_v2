cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity3 LANGUAGES MikroC)
else()
    project(lib_proximity3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity3 STATIC
        src/proximity3.c
        include/proximity3.h
)
add_library(Click.Proximity3  ALIAS lib_proximity3)



target_include_directories(lib_proximity3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity3 PUBLIC MikroSDK.Driver)
