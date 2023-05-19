cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless6 LANGUAGES MikroC)
else()
    project(lib_brushless6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless6 STATIC
        src/brushless6.c
        include/brushless6.h
)
add_library(Click.Brushless6  ALIAS lib_brushless6)



target_include_directories(lib_brushless6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless6 PUBLIC MikroSDK.Driver)
