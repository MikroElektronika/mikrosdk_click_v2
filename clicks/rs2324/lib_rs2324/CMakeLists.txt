cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs2324 LANGUAGES MikroC)
else()
    project(lib_rs2324 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs2324 STATIC
        src/rs2324.c
        include/rs2324.h
)
add_library(Click.RS2324  ALIAS lib_rs2324)



target_include_directories(lib_rs2324 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs2324 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs2324 PUBLIC MikroSDK.Driver)

