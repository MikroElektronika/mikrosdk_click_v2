cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent15 LANGUAGES MikroC)
else()
    project(lib_hallcurrent15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent15 STATIC
        src/hallcurrent15.c
        include/hallcurrent15.h
)
add_library(Click.HallCurrent15  ALIAS lib_hallcurrent15)



target_include_directories(lib_hallcurrent15 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent15 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent15 PUBLIC MikroSDK.Driver)
