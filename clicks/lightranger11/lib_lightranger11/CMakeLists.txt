cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lightranger11 LANGUAGES MikroC)
else()
    project(lib_lightranger11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lightranger11 STATIC
        src/lightranger11.c
        include/lightranger11.h
        include/firmware_buffers.h
)
add_library(Click.LightRanger11  ALIAS lib_lightranger11)



target_include_directories(lib_lightranger11 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lightranger11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lightranger11 PUBLIC MikroSDK.Driver)

