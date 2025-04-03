cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_environment5 LANGUAGES MikroC)
else()
    project(lib_environment5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_environment5 STATIC
        src/environment5.c
        include/environment5.h
)
add_library(Click.Environment5  ALIAS lib_environment5)



target_include_directories(lib_environment5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_environment5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_environment5 PUBLIC MikroSDK.Driver)

