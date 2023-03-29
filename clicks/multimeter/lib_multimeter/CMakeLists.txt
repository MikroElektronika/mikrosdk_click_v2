cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_multimeter LANGUAGES MikroC)
else()
    project(lib_multimeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_multimeter STATIC
        src/multimeter.c
        include/multimeter.h
)
add_library(Click.Multimeter  ALIAS lib_multimeter)



target_include_directories(lib_multimeter PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_multimeter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_multimeter PUBLIC MikroSDK.Driver)
