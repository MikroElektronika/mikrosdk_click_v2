cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c420mar LANGUAGES MikroC)
else()
    project(lib_c420mar LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c420mar STATIC
        src/c420mar.c
        include/c420mar.h
)
add_library(Click.420MaR  ALIAS lib_c420mar)



target_include_directories(lib_c420mar PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c420mar PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c420mar PUBLIC MikroSDK.Driver)
