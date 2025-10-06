cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbuart6 LANGUAGES MikroC)
else()
    project(lib_usbuart6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbuart6 STATIC
        src/usbuart6.c
        include/usbuart6.h
)
add_library(Click.USBUART6  ALIAS lib_usbuart6)



target_include_directories(lib_usbuart6 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbuart6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbuart6 PUBLIC MikroSDK.Driver)

