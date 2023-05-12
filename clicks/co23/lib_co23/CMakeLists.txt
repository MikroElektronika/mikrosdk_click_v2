cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_co23 LANGUAGES MikroC)
else()
    project(lib_co23 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_co23 STATIC
        src/co23.c
        include/co23.h
)
add_library(Click.CO23  ALIAS lib_co23)



target_include_directories(lib_co23 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_co23 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_co23 PUBLIC MikroSDK.Driver)

