cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_motion3 LANGUAGES MikroC)
else()
    project(lib_motion3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_motion3 STATIC
        src/motion3.c
        include/motion3.h
)
add_library(Click.Motion3  ALIAS lib_motion3)



target_include_directories(lib_motion3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_motion3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_motion3 PUBLIC MikroSDK.Driver)
