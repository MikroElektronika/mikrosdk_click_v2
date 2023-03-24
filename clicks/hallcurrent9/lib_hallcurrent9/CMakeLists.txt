cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent9 LANGUAGES MikroC)
else()
    project(lib_hallcurrent9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent9 STATIC
        src/hallcurrent9.c
        include/hallcurrent9.h
)
add_library(Click.HallCurrent9  ALIAS lib_hallcurrent9)



target_include_directories(lib_hallcurrent9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent9 PUBLIC MikroSDK.Driver)
