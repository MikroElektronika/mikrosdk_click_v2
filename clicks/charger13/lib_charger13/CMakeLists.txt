cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_charger13 LANGUAGES MikroC)
else()
    project(lib_charger13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_charger13 STATIC
        src/charger13.c
        include/charger13.h
)
add_library(Click.Charger13  ALIAS lib_charger13)



target_include_directories(lib_charger13 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_charger13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_charger13 PUBLIC MikroSDK.Driver)
