cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_surfacetemp2 LANGUAGES MikroC)
else()
    project(lib_surfacetemp2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_surfacetemp2 STATIC
        src/surfacetemp2.c
        include/surfacetemp2.h
)
add_library(Click.SurfaceTemp2  ALIAS lib_surfacetemp2)



target_include_directories(lib_surfacetemp2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_surfacetemp2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_surfacetemp2 PUBLIC MikroSDK.Driver)
