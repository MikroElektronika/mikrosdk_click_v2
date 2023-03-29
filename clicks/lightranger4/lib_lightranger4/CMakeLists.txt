cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lightranger4 LANGUAGES MikroC)
else()
    project(lib_lightranger4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lightranger4 STATIC
        src/lightranger4.c
        include/lightranger4.h
)
add_library(Click.LightRanger4  ALIAS lib_lightranger4)



target_include_directories(lib_lightranger4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lightranger4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lightranger4 PUBLIC MikroSDK.Driver)
