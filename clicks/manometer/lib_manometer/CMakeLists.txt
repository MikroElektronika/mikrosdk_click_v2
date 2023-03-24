cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_manometer LANGUAGES MikroC)
else()
    project(lib_manometer LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_manometer STATIC
        src/manometer.c
        include/manometer.h
)
add_library(Click.Manometer  ALIAS lib_manometer)



target_include_directories(lib_manometer PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_manometer PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_manometer PUBLIC MikroSDK.Driver)
