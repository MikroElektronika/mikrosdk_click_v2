cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current4 LANGUAGES MikroC)
else()
    project(lib_current4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current4 STATIC
        src/current4.c
        include/current4.h
)
add_library(Click.Current4  ALIAS lib_current4)



target_include_directories(lib_current4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current4 PUBLIC MikroSDK.Driver)
