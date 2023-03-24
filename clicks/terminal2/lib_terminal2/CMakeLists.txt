cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_terminal2 LANGUAGES MikroC)
else()
    project(lib_terminal2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_terminal2 STATIC
        src/terminal2.c
        include/terminal2.h
)
add_library(Click.Terminal2  ALIAS lib_terminal2)



target_include_directories(lib_terminal2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_terminal2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_terminal2 PUBLIC MikroSDK.Driver)
