cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current11 LANGUAGES MikroC)
else()
    project(lib_current11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current11 STATIC
        src/current11.c
        include/current11.h
)
add_library(Click.Current11  ALIAS lib_current11)



target_include_directories(lib_current11 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current11 PUBLIC MikroSDK.Driver)

