cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_charger3 LANGUAGES MikroC)
else()
    project(lib_charger3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_charger3 STATIC
        src/charger3.c
        include/charger3.h
)
add_library(Click.Charger3  ALIAS lib_charger3)



target_include_directories(lib_charger3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_charger3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_charger3 PUBLIC MikroSDK.Driver)
