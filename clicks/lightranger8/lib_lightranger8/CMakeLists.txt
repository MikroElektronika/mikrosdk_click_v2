cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lightranger8 LANGUAGES MikroC)
else()
    project(lib_lightranger8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lightranger8 STATIC
        src/lightranger8.c
        include/lightranger8.h
)
add_library(Click.LightRanger8  ALIAS lib_lightranger8)



target_include_directories(lib_lightranger8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lightranger8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lightranger8 PUBLIC MikroSDK.Driver)
