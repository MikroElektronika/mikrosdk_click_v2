cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent5 LANGUAGES MikroC)
else()
    project(lib_hallcurrent5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent5 STATIC
        src/hallcurrent5.c
        include/hallcurrent5.h
)
add_library(Click.HallCurrent5  ALIAS lib_hallcurrent5)



target_include_directories(lib_hallcurrent5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent5 PUBLIC MikroSDK.Driver)
