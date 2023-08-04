cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_zerocross LANGUAGES MikroC)
else()
    project(lib_zerocross LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_zerocross STATIC
        src/zerocross.c
        include/zerocross.h
)
add_library(Click.ZeroCross  ALIAS lib_zerocross)



target_include_directories(lib_zerocross PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_zerocross PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_zerocross PUBLIC MikroSDK.Driver)

