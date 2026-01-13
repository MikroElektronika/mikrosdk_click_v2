cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity23 LANGUAGES MikroC)
else()
    project(lib_proximity23 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity23 STATIC
        src/proximity23.c
        include/proximity23.h
)
add_library(Click.Proximity23  ALIAS lib_proximity23)



target_include_directories(lib_proximity23 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity23 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity23 PUBLIC MikroSDK.Driver)

