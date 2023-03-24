cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs4855v LANGUAGES MikroC)
else()
    project(lib_rs4855v LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs4855v STATIC
        src/rs4855v.c
        include/rs4855v.h
)
add_library(Click.RS4855V  ALIAS lib_rs4855v)



target_include_directories(lib_rs4855v PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs4855v PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs4855v PUBLIC MikroSDK.Driver)
