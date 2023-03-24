cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbuart5 LANGUAGES MikroC)
else()
    project(lib_usbuart5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbuart5 STATIC
        src/usbuart5.c
        include/usbuart5.h
)
add_library(Click.USBUART5  ALIAS lib_usbuart5)



target_include_directories(lib_usbuart5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbuart5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbuart5 PUBLIC MikroSDK.Driver)

