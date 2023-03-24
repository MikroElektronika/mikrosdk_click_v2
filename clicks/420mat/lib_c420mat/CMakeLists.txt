cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c420mat LANGUAGES MikroC)
else()
    project(lib_c420mat LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c420mat STATIC
        src/c420mat.c
        include/c420mat.h
)
add_library(Click.420mat  ALIAS lib_c420mat)



target_include_directories(lib_c420mat PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c420mat PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c420mat PUBLIC MikroSDK.Driver)
