cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bargraph2 LANGUAGES MikroC)
else()
    project(lib_bargraph2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bargraph2 STATIC
        src/bargraph2.c
        include/bargraph2.h
)
add_library(Click.Bargraph2  ALIAS lib_bargraph2)



target_include_directories(lib_bargraph2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bargraph2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bargraph2 PUBLIC MikroSDK.Driver)
