cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lightranger9 LANGUAGES MikroC)
else()
    project(lib_lightranger9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lightranger9 STATIC
        src/lightranger9.c
        include/lightranger9.h    include/tof_bin_image.h
)
add_library(Click.LightRanger9  ALIAS lib_lightranger9)



target_include_directories(lib_lightranger9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lightranger9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lightranger9 PUBLIC MikroSDK.Driver)
