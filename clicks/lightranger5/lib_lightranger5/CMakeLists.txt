cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lightranger5 LANGUAGES MikroC)
else()
    project(lib_lightranger5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lightranger5 STATIC
        src/lightranger5.c
        include/lightranger5.h
)
add_library(Click.LightRanger5  ALIAS lib_lightranger5)



target_include_directories(lib_lightranger5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lightranger5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lightranger5 PUBLIC MikroSDK.Driver)
