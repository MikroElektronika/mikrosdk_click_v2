cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pot LANGUAGES MikroC)
else()
    project(lib_pot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pot STATIC
        src/pot.c
        include/pot.h
)
add_library(Click.Pot  ALIAS lib_pot)



target_include_directories(lib_pot PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pot PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pot PUBLIC MikroSDK.Driver)
