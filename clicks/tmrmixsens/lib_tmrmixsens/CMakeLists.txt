cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tmrmixsens LANGUAGES MikroC)
else()
    project(lib_tmrmixsens LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tmrmixsens STATIC
        src/tmrmixsens.c
        include/tmrmixsens.h
)
add_library(Click.Tmrmixsens  ALIAS lib_tmrmixsens)



target_include_directories(lib_tmrmixsens PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tmrmixsens PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tmrmixsens PUBLIC MikroSDK.Driver)
