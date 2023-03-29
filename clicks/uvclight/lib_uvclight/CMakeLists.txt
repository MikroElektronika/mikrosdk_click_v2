cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uvclight LANGUAGES MikroC)
else()
    project(lib_uvclight LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uvclight STATIC
        src/uvclight.c
        include/uvclight.h
)
add_library(Click.UvcLight  ALIAS lib_uvclight)



target_include_directories(lib_uvclight PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uvclight PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uvclight PUBLIC MikroSDK.Driver)
