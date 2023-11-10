cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent18 LANGUAGES MikroC)
else()
    project(lib_hallcurrent18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent18 STATIC
        src/hallcurrent18.c
        include/hallcurrent18.h
)
add_library(Click.HallCurrent18  ALIAS lib_hallcurrent18)



target_include_directories(lib_hallcurrent18 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent18 PUBLIC MikroSDK.Driver)

