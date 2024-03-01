cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ezocarrierorp LANGUAGES MikroC)
else()
    project(lib_ezocarrierorp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ezocarrierorp STATIC
        src/ezocarrierorp.c
        include/ezocarrierorp.h
)
add_library(Click.EZOCarrierORP  ALIAS lib_ezocarrierorp)



target_include_directories(lib_ezocarrierorp PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ezocarrierorp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ezocarrierorp PUBLIC MikroSDK.Driver)

