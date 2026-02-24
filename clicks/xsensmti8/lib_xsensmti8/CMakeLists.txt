cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_xsensmti8 LANGUAGES MikroC)
else()
    project(lib_xsensmti8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_xsensmti8 STATIC
        src/xsensmti8.c
        include/xsensmti8.h
)
add_library(Click.XSENSMTi8  ALIAS lib_xsensmti8)



target_include_directories(lib_xsensmti8 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_xsensmti8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_xsensmti8 PUBLIC MikroSDK.Driver)

