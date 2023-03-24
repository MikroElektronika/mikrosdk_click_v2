cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vavpress LANGUAGES MikroC)
else()
    project(lib_vavpress LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vavpress STATIC
        src/vavpress.c
        include/vavpress.h
)
add_library(Click.VavPress  ALIAS lib_vavpress)



target_include_directories(lib_vavpress PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vavpress PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vavpress PUBLIC MikroSDK.Driver)
