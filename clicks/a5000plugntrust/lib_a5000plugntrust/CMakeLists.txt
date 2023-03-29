cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_a5000plugntrust LANGUAGES MikroC)
else()
    project(lib_a5000plugntrust LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_a5000plugntrust STATIC
        src/a5000plugntrust.c
        include/a5000plugntrust.h
)
add_library(Click.A5000PlugnTrust  ALIAS lib_a5000plugntrust)



target_include_directories(lib_a5000plugntrust PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_a5000plugntrust PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_a5000plugntrust PUBLIC MikroSDK.Driver)
