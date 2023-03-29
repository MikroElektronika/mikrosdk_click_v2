cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pot3 LANGUAGES MikroC)
else()
    project(lib_pot3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pot3 STATIC
        src/pot3.c
        include/pot3.h
)
add_library(Click.Pot3  ALIAS lib_pot3)



target_include_directories(lib_pot3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pot3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pot3 PUBLIC MikroSDK.Driver)
