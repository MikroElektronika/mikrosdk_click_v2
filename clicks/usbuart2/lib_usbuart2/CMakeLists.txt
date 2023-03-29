cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbuart2 LANGUAGES MikroC)
else()
    project(lib_usbuart2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbuart2 STATIC
        src/usbuart2.c
        include/usbuart2.h
)
add_library(Click.USBUART2  ALIAS lib_usbuart2)



target_include_directories(lib_usbuart2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbuart2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbuart2 PUBLIC MikroSDK.Driver)
