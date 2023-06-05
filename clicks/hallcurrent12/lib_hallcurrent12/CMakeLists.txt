cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent12 LANGUAGES MikroC)
else()
    project(lib_hallcurrent12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent12 STATIC
        src/hallcurrent12.c
        include/hallcurrent12.h
)
add_library(Click.HallCurrent12  ALIAS lib_hallcurrent12)



target_include_directories(lib_hallcurrent12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent12 PUBLIC MikroSDK.Driver)
