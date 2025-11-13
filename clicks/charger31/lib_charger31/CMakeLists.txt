cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_charger31 LANGUAGES MikroC)
else()
    project(lib_charger31 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_charger31 STATIC
        src/charger31.c
        include/charger31.h
)
add_library(Click.Charger31  ALIAS lib_charger31)



target_include_directories(lib_charger31 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_charger31 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_charger31 PUBLIC MikroSDK.Driver)

