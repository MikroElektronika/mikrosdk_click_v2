cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pir2 LANGUAGES MikroC)
else()
    project(lib_pir2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pir2 STATIC
        src/pir2.c
        include/pir2.h
)
add_library(Click.PIR2  ALIAS lib_pir2)



target_include_directories(lib_pir2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pir2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pir2 PUBLIC MikroSDK.Driver)

