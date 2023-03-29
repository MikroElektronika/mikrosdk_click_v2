cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver11 LANGUAGES MikroC)
else()
    project(lib_leddriver11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver11 STATIC
        src/leddriver11.c
        include/leddriver11.h
)
add_library(Click.LEDDriver11  ALIAS lib_leddriver11)



target_include_directories(lib_leddriver11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver11 PUBLIC MikroSDK.Driver)
