cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless18 LANGUAGES MikroC)
else()
    project(lib_brushless18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless18 STATIC
        src/brushless18.c
        include/brushless18.h
)
add_library(Click.Brushless18  ALIAS lib_brushless18)



target_include_directories(lib_brushless18 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless18 PUBLIC MikroSDK.Driver)

