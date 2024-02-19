cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_battboost LANGUAGES MikroC)
else()
    project(lib_battboost LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_battboost STATIC
        src/battboost.c
        include/battboost.h
)
add_library(Click.BATTBoost  ALIAS lib_battboost)



target_include_directories(lib_battboost PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_battboost PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_battboost PUBLIC MikroSDK.Driver)

