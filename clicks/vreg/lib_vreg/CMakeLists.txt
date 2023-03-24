cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vreg LANGUAGES MikroC)
else()
    project(lib_vreg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vreg STATIC
        src/vreg.c
        include/vreg.h
)
add_library(Click.Vreg  ALIAS lib_vreg)



target_include_directories(lib_vreg PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vreg PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vreg PUBLIC MikroSDK.Driver)
