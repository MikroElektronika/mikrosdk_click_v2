cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lightranger LANGUAGES MikroC)
else()
    project(lib_lightranger LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lightranger STATIC
        src/lightranger.c
        include/lightranger.h
)
add_library(Click.LightRanger  ALIAS lib_lightranger)



target_include_directories(lib_lightranger PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lightranger PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lightranger PUBLIC MikroSDK.Driver)
