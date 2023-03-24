cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_charger16 LANGUAGES MikroC)
else()
    project(lib_charger16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_charger16 STATIC
        src/charger16.c
        include/charger16.h
)
add_library(Click.Charger16  ALIAS lib_charger16)



target_include_directories(lib_charger16 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_charger16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_charger16 PUBLIC MikroSDK.Driver)
