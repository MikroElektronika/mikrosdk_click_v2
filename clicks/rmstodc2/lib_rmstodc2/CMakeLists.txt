cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rmstodc2 LANGUAGES MikroC)
else()
    project(lib_rmstodc2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rmstodc2 STATIC
        src/rmstodc2.c
        include/rmstodc2.h
)
add_library(Click.RMStoDC2  ALIAS lib_rmstodc2)



target_include_directories(lib_rmstodc2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rmstodc2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rmstodc2 PUBLIC MikroSDK.Driver)

