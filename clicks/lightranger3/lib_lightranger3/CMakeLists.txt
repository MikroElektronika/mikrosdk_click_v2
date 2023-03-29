cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lightranger3 LANGUAGES MikroC)
else()
    project(lib_lightranger3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lightranger3 STATIC
        src/lightranger3.c
        include/lightranger3.h
)
add_library(Click.LightRanger3  ALIAS lib_lightranger3)



target_include_directories(lib_lightranger3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lightranger3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lightranger3 PUBLIC MikroSDK.Driver)
