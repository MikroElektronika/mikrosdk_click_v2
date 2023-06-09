cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pll LANGUAGES MikroC)
else()
    project(lib_pll LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pll STATIC
        src/pll.c
        include/pll.h
)
add_library(Click.Pll  ALIAS lib_pll)



target_include_directories(lib_pll PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pll PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pll PUBLIC MikroSDK.Driver)
