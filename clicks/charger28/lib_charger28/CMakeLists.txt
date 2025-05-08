cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_charger28 LANGUAGES MikroC)
else()
    project(lib_charger28 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_charger28 STATIC
        src/charger28.c
        include/charger28.h
)
add_library(Click.Charger28  ALIAS lib_charger28)



target_include_directories(lib_charger28 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_charger28 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_charger28 PUBLIC MikroSDK.Driver)

