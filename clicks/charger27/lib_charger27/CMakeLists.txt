cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_charger27 LANGUAGES MikroC)
else()
    project(lib_charger27 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_charger27 STATIC
        src/charger27.c
        include/charger27.h
)
add_library(Click.Charger27  ALIAS lib_charger27)



target_include_directories(lib_charger27 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_charger27 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_charger27 PUBLIC MikroSDK.Driver)

