cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_touchkey4 LANGUAGES MikroC)
else()
    project(lib_touchkey4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_touchkey4 STATIC
        src/touchkey4.c
        include/touchkey4.h
)
add_library(Click.TouchKey4  ALIAS lib_touchkey4)



target_include_directories(lib_touchkey4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_touchkey4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_touchkey4 PUBLIC MikroSDK.Driver)
