cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_optoencoder LANGUAGES MikroC)
else()
    project(lib_optoencoder LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_optoencoder STATIC
        src/optoencoder.c
        include/optoencoder.h
)
add_library(Click.OptoEncoder  ALIAS lib_optoencoder)



target_include_directories(lib_optoencoder PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_optoencoder PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_optoencoder PUBLIC MikroSDK.Driver)
