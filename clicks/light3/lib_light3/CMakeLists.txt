cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_light3 LANGUAGES MikroC)
else()
    project(lib_light3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_light3 STATIC
        src/light3.c
        include/light3.h
)
add_library(Click.Light3  ALIAS lib_light3)



target_include_directories(lib_light3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_light3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_light3 PUBLIC MikroSDK.Driver)

