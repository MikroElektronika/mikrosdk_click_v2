cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_charger9 LANGUAGES MikroC)
else()
    project(lib_charger9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_charger9 STATIC
        src/charger9.c
        include/charger9.h
)
add_library(Click.Charger9  ALIAS lib_charger9)



target_include_directories(lib_charger9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_charger9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_charger9 PUBLIC MikroSDK.Driver)
