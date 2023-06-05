cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent8120a LANGUAGES MikroC)
else()
    project(lib_hallcurrent8120a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent8120a STATIC
        src/hallcurrent8120a.c
        include/hallcurrent8120a.h
)
add_library(Click.HallCurrent8120A  ALIAS lib_hallcurrent8120a)



target_include_directories(lib_hallcurrent8120a PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent8120a PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent8120a PUBLIC MikroSDK.Driver)
