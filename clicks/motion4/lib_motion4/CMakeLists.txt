cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_motion4 LANGUAGES MikroC)
else()
    project(lib_motion4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_motion4 STATIC
        src/motion4.c
        include/motion4.h
)
add_library(Click.Motion4  ALIAS lib_motion4)



target_include_directories(lib_motion4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_motion4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_motion4 PUBLIC MikroSDK.Driver)
