cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current6 LANGUAGES MikroC)
else()
    project(lib_current6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current6 STATIC
        src/current6.c
        include/current6.h
)
add_library(Click.Current6  ALIAS lib_current6)



target_include_directories(lib_current6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current6 PUBLIC MikroSDK.Driver)
