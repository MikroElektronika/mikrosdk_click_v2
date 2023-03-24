cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_haptic LANGUAGES MikroC)
else()
    project(lib_haptic LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_haptic STATIC
        src/haptic.c
        include/haptic.h
)
add_library(Click.Haptic  ALIAS lib_haptic)



target_include_directories(lib_haptic PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_haptic PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_haptic PUBLIC MikroSDK.Driver)
