cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accurrent2 LANGUAGES MikroC)
else()
    project(lib_accurrent2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accurrent2 STATIC
        src/accurrent2.c
        include/accurrent2.h
)
add_library(Click.ACCurrent2  ALIAS lib_accurrent2)



target_include_directories(lib_accurrent2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accurrent2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accurrent2 PUBLIC MikroSDK.Driver)

