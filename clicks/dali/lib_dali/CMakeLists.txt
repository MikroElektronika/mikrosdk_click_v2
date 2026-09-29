cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dali LANGUAGES MikroC)
else()
    project(lib_dali LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dali STATIC
        src/dali.c
        include/dali.h
)
add_library(Click.DALI  ALIAS lib_dali)



target_include_directories(lib_dali PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dali PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dali PUBLIC MikroSDK.Driver)

