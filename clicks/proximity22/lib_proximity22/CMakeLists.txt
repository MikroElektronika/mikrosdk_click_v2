cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity22 LANGUAGES MikroC)
else()
    project(lib_proximity22 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity22 STATIC
        src/proximity22.c
        include/proximity22.h
)
add_library(Click.Proximity22  ALIAS lib_proximity22)



target_include_directories(lib_proximity22 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity22 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity22 PUBLIC MikroSDK.Driver)

