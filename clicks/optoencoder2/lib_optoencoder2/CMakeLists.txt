cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_optoencoder2 LANGUAGES MikroC)
else()
    project(lib_optoencoder2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_optoencoder2 STATIC
        src/optoencoder2.c
        include/optoencoder2.h
)
add_library(Click.OptoEncoder2  ALIAS lib_optoencoder2)



target_include_directories(lib_optoencoder2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_optoencoder2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_optoencoder2 PUBLIC MikroSDK.Driver)
