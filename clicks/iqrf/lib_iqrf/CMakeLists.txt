cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_iqrf LANGUAGES MikroC)
else()
    project(lib_iqrf LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_iqrf STATIC
        src/iqrf.c
        include/iqrf.h
)
add_library(Click.iqRF  ALIAS lib_iqrf)



target_include_directories(lib_iqrf PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_iqrf PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_iqrf PUBLIC MikroSDK.Driver)
