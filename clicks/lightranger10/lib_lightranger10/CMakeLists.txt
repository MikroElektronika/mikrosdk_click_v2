cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lightranger10 LANGUAGES MikroC)
else()
    project(lib_lightranger10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lightranger10 STATIC
        src/lightranger10.c
        include/lightranger10.h
)
add_library(Click.LightRanger10  ALIAS lib_lightranger10)



target_include_directories(lib_lightranger10 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lightranger10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lightranger10 PUBLIC MikroSDK.Driver)
