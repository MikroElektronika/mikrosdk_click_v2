cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_counter LANGUAGES MikroC)
else()
    project(lib_counter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_counter STATIC
        src/counter.c
        include/counter.h
)
add_library(Click.Counter  ALIAS lib_counter)



target_include_directories(lib_counter PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_counter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_counter PUBLIC MikroSDK.Driver)
