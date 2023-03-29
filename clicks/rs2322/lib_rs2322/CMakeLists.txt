cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs2322 LANGUAGES MikroC)
else()
    project(lib_rs2322 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs2322 STATIC
        src/rs2322.c
        include/rs2322.h
)
add_library(Click.Rs2322  ALIAS lib_rs2322)



target_include_directories(lib_rs2322 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs2322 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs2322 PUBLIC MikroSDK.Driver)
