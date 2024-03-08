cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ezocarrierec LANGUAGES MikroC)
else()
    project(lib_ezocarrierec LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ezocarrierec STATIC
        src/ezocarrierec.c
        include/ezocarrierec.h
)
add_library(Click.EZOCarrierEC  ALIAS lib_ezocarrierec)



target_include_directories(lib_ezocarrierec PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ezocarrierec PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ezocarrierec PUBLIC MikroSDK.Driver)

