cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_charger12 LANGUAGES MikroC)
else()
    project(lib_charger12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_charger12 STATIC
        src/charger12.c
        include/charger12.h
)
add_library(Click.Charger12  ALIAS lib_charger12)



target_include_directories(lib_charger12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_charger12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_charger12 PUBLIC MikroSDK.Driver)
