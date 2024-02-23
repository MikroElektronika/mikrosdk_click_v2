cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ezocarrierrtd LANGUAGES MikroC)
else()
    project(lib_ezocarrierrtd LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ezocarrierrtd STATIC
        src/ezocarrierrtd.c
        include/ezocarrierrtd.h
)
add_library(Click.EZOCarrierRTD  ALIAS lib_ezocarrierrtd)



target_include_directories(lib_ezocarrierrtd PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ezocarrierrtd PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ezocarrierrtd PUBLIC MikroSDK.Driver)

