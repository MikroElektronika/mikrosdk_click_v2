cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lr11915mhz LANGUAGES MikroC)
else()
    project(lib_lr11915mhz LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lr11915mhz STATIC
        src/lr11915mhz.c
        include/lr11915mhz.h
)
add_library(Click.LR11915MHz  ALIAS lib_lr11915mhz)



target_include_directories(lib_lr11915mhz PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lr11915mhz PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lr11915mhz PUBLIC MikroSDK.Driver)

