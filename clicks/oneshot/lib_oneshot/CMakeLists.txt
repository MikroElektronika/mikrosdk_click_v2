cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_oneshot LANGUAGES MikroC)
else()
    project(lib_oneshot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_oneshot STATIC
        src/oneshot.c
        include/oneshot.h
)
add_library(Click.OneShot  ALIAS lib_oneshot)



target_include_directories(lib_oneshot PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_oneshot PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_oneshot PUBLIC MikroSDK.Driver)
