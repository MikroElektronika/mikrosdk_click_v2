cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_oximeter LANGUAGES MikroC)
else()
    project(lib_oximeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_oximeter STATIC
        src/oximeter.c
        include/oximeter.h
)
add_library(Click.Oximeter  ALIAS lib_oximeter)



target_include_directories(lib_oximeter PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_oximeter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_oximeter PUBLIC MikroSDK.Driver)
