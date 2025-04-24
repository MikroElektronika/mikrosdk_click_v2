cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent22 LANGUAGES MikroC)
else()
    project(lib_hallcurrent22 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent22 STATIC
        src/hallcurrent22.c
        include/hallcurrent22.h
)
add_library(Click.HallCurrent22  ALIAS lib_hallcurrent22)



target_include_directories(lib_hallcurrent22 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent22 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent22 PUBLIC MikroSDK.Driver)

