cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_environment7 LANGUAGES MikroC)
else()
    project(lib_environment7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_environment7 STATIC
        src/environment7.c
        include/environment7.h
)
add_library(Click.Environment7  ALIAS lib_environment7)



target_include_directories(lib_environment7 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_environment7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_environment7 PUBLIC MikroSDK.Driver)

