cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hztov LANGUAGES MikroC)
else()
    project(lib_hztov LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hztov STATIC
        src/hztov.c
        include/hztov.h
)
add_library(Click.HzToV  ALIAS lib_hztov)



target_include_directories(lib_hztov PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hztov PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hztov PUBLIC MikroSDK.Driver)
