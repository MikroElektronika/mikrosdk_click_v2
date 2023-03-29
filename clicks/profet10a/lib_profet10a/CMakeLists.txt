cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_profet10a LANGUAGES MikroC)
else()
    project(lib_profet10a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_profet10a STATIC
        src/profet10a.c
        include/profet10a.h
)
add_library(Click.PROFET10A  ALIAS lib_profet10a)



target_include_directories(lib_profet10a PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_profet10a PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_profet10a PUBLIC MikroSDK.Driver)
