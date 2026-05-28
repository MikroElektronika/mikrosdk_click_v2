cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity25 LANGUAGES MikroC)
else()
    project(lib_proximity25 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity25 STATIC
        src/proximity25.c
        include/proximity25.h
)
add_library(Click.Proximity25  ALIAS lib_proximity25)



target_include_directories(lib_proximity25 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity25 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity25 PUBLIC MikroSDK.Driver)

