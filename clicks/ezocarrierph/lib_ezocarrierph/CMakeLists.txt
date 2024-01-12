cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ezocarrierph LANGUAGES MikroC)
else()
    project(lib_ezocarrierph LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ezocarrierph STATIC
        src/ezocarrierph.c
        include/ezocarrierph.h
)
add_library(Click.EZOCarrierpH  ALIAS lib_ezocarrierph)



target_include_directories(lib_ezocarrierph PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ezocarrierph PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ezocarrierph PUBLIC MikroSDK.Driver)

