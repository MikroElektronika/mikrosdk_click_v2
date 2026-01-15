cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pir4 LANGUAGES MikroC)
else()
    project(lib_pir4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pir4 STATIC
        src/pir4.c
        include/pir4.h
)
add_library(Click.PIR4  ALIAS lib_pir4)



target_include_directories(lib_pir4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pir4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pir4 PUBLIC MikroSDK.Driver)

