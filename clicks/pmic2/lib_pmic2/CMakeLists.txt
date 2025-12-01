cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pmic2 LANGUAGES MikroC)
else()
    project(lib_pmic2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pmic2 STATIC
        src/pmic2.c
        include/pmic2.h
)
add_library(Click.PMIC2  ALIAS lib_pmic2)



target_include_directories(lib_pmic2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pmic2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pmic2 PUBLIC MikroSDK.Driver)

