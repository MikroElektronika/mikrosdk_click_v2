cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lightranger7 LANGUAGES MikroC)
else()
    project(lib_lightranger7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lightranger7 STATIC
        src/lightranger7.c
        include/lightranger7.h
)
add_library(Click.LightRanger7  ALIAS lib_lightranger7)



target_include_directories(lib_lightranger7 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lightranger7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lightranger7 PUBLIC MikroSDK.Driver)

