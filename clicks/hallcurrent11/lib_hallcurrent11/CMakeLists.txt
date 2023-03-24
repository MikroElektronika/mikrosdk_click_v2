cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent11 LANGUAGES MikroC)
else()
    project(lib_hallcurrent11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent11 STATIC
        src/hallcurrent11.c
        include/hallcurrent11.h
)
add_library(Click.HallCurrent11  ALIAS lib_hallcurrent11)



target_include_directories(lib_hallcurrent11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent11 PUBLIC MikroSDK.Driver)
