cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_light LANGUAGES MikroC)
else()
    project(lib_light LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_light STATIC
        src/light.c
        include/light.h
)
add_library(Click.Light  ALIAS lib_light)



target_include_directories(lib_light PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_light PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_light PUBLIC MikroSDK.Driver)
