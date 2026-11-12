cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pmic4 LANGUAGES MikroC)
else()
    project(lib_pmic4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pmic4 STATIC
        src/pmic4.c
        include/pmic4.h
)
add_library(Click.PMIC4  ALIAS lib_pmic4)



target_include_directories(lib_pmic4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pmic4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pmic4 PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
