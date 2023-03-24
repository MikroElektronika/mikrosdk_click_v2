cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_profet23a LANGUAGES MikroC)
else()
    project(lib_profet23a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_profet23a STATIC
        src/profet23a.c
        include/profet23a.h
)
add_library(Click.PROFET23A  ALIAS lib_profet23a)



target_include_directories(lib_profet23a PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_profet23a PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_profet23a PUBLIC MikroSDK.Driver)
