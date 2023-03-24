cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pir LANGUAGES MikroC)
else()
    project(lib_pir LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pir STATIC
        src/pir.c
        include/pir.h
)
add_library(Click.Pir  ALIAS lib_pir)



target_include_directories(lib_pir PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pir PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pir PUBLIC MikroSDK.Driver)
