cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck18 LANGUAGES MikroC)
else()
    project(lib_buck18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck18 STATIC
        src/buck18.c
        include/buck18.h
)
add_library(Click.Buck18  ALIAS lib_buck18)



target_include_directories(lib_buck18 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck18 PUBLIC MikroSDK.Driver)

