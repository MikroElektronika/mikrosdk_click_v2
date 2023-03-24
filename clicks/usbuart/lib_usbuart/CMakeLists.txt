cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbuart LANGUAGES MikroC)
else()
    project(lib_usbuart LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbuart STATIC
        src/usbuart.c
        include/usbuart.h
)
add_library(Click.USBUART  ALIAS lib_usbuart)



target_include_directories(lib_usbuart PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbuart PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbuart PUBLIC MikroSDK.Driver)
