cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buzz2 LANGUAGES MikroC)
else()
    project(lib_buzz2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buzz2 STATIC
        src/buzz2.c
        include/buzz2.h
)
add_library(Click.Buzz2  ALIAS lib_buzz2)



target_include_directories(lib_buzz2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buzz2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buzz2 PUBLIC MikroSDK.Driver)
