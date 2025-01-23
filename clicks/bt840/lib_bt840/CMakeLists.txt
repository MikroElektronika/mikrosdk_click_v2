cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bt840 LANGUAGES MikroC)
else()
    project(lib_bt840 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bt840 STATIC
        src/bt840.c
        include/bt840.h
)
add_library(Click.BT840  ALIAS lib_bt840)



target_include_directories(lib_bt840 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bt840 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bt840 PUBLIC MikroSDK.Driver)

