cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lightranger13 LANGUAGES MikroC)
else()
    project(lib_lightranger13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lightranger13 STATIC
        src/lightranger13.c
        include/lightranger13.h
)
add_library(Click.LightRanger13  ALIAS lib_lightranger13)



target_include_directories(lib_lightranger13 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lightranger13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lightranger13 PUBLIC MikroSDK.Driver)

