cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_profet27a LANGUAGES MikroC)
else()
    project(lib_profet27a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_profet27a STATIC
        src/profet27a.c
        include/profet27a.h
)
add_library(Click.PROFET27A  ALIAS lib_profet27a)



target_include_directories(lib_profet27a PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_profet27a PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_profet27a PUBLIC MikroSDK.Driver)
