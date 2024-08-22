cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pmic LANGUAGES MikroC)
else()
    project(lib_pmic LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pmic STATIC
        src/pmic.c
        include/pmic.h
)
add_library(Click.PMIC  ALIAS lib_pmic)



target_include_directories(lib_pmic PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pmic PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pmic PUBLIC MikroSDK.Driver)

