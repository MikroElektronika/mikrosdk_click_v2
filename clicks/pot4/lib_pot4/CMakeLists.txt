cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pot4 LANGUAGES MikroC)
else()
    project(lib_pot4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pot4 STATIC
        src/pot4.c
        include/pot4.h
)
add_library(Click.POT4  ALIAS lib_pot4)



target_include_directories(lib_pot4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pot4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pot4 PUBLIC MikroSDK.Driver)
