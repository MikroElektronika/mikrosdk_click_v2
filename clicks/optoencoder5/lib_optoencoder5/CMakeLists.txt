cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_optoencoder5 LANGUAGES MikroC)
else()
    project(lib_optoencoder5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_optoencoder5 STATIC
        src/optoencoder5.c
        include/optoencoder5.h
)
add_library(Click.OptoEncoder5  ALIAS lib_optoencoder5)



target_include_directories(lib_optoencoder5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_optoencoder5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_optoencoder5 PUBLIC MikroSDK.Driver)

