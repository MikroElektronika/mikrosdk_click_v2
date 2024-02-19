cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ezocarrierdo LANGUAGES MikroC)
else()
    project(lib_ezocarrierdo LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ezocarrierdo STATIC
        src/ezocarrierdo.c
        include/ezocarrierdo.h
)
add_library(Click.EZOCarrierDO  ALIAS lib_ezocarrierdo)



target_include_directories(lib_ezocarrierdo PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ezocarrierdo PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ezocarrierdo PUBLIC MikroSDK.Driver)

