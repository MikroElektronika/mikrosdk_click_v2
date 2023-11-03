cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_charger26 LANGUAGES MikroC)
else()
    project(lib_charger26 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_charger26 STATIC
        src/charger26.c
        include/charger26.h
)
add_library(Click.Charger26  ALIAS lib_charger26)



target_include_directories(lib_charger26 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_charger26 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_charger26 PUBLIC MikroSDK.Driver)

