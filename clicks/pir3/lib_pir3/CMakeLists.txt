cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pir3 LANGUAGES MikroC)
else()
    project(lib_pir3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pir3 STATIC
        src/pir3.c
        include/pir3.h
)
add_library(Click.PIR3  ALIAS lib_pir3)



target_include_directories(lib_pir3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pir3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pir3 PUBLIC MikroSDK.Driver)

