cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_charger24 LANGUAGES MikroC)
else()
    project(lib_charger24 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_charger24 STATIC
        src/charger24.c
        include/charger24.h
)
add_library(Click.Charger24  ALIAS lib_charger24)



target_include_directories(lib_charger24 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_charger24 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_charger24 PUBLIC MikroSDK.Driver)

