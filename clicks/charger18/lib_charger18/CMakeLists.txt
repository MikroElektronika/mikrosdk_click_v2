cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_charger18 LANGUAGES MikroC)
else()
    project(lib_charger18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_charger18 STATIC
        src/charger18.c
        include/charger18.h
)
add_library(Click.Charger18  ALIAS lib_charger18)



target_include_directories(lib_charger18 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_charger18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_charger18 PUBLIC MikroSDK.Driver)
