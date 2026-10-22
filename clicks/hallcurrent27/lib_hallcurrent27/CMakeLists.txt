cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent27 LANGUAGES MikroC)
else()
    project(lib_hallcurrent27 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent27 STATIC
        src/hallcurrent27.c
        include/hallcurrent27.h
)
add_library(Click.HallCurrent27  ALIAS lib_hallcurrent27)



target_include_directories(lib_hallcurrent27 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent27 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent27 PUBLIC MikroSDK.Driver)

