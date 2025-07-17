cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_powerstep LANGUAGES MikroC)
else()
    project(lib_powerstep LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_powerstep STATIC
        src/powerstep.c
        include/powerstep.h
)
add_library(Click.PowerStep  ALIAS lib_powerstep)



target_include_directories(lib_powerstep PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_powerstep PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_powerstep PUBLIC MikroSDK.Driver)

