cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pot2 LANGUAGES MikroC)
else()
    project(lib_pot2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pot2 STATIC
        src/pot2.c
        include/pot2.h
)
add_library(Click.Pot2  ALIAS lib_pot2)



target_include_directories(lib_pot2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pot2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pot2 PUBLIC MikroSDK.Driver)
