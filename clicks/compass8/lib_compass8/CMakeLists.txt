cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_compass8 LANGUAGES MikroC)
else()
    project(lib_compass8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_compass8 STATIC
        src/compass8.c
        include/compass8.h
)
add_library(Click.Compass8  ALIAS lib_compass8)



target_include_directories(lib_compass8 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_compass8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_compass8 PUBLIC MikroSDK.Driver)

