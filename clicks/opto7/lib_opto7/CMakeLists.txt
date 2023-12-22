cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_opto7 LANGUAGES MikroC)
else()
    project(lib_opto7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_opto7 STATIC
        src/opto7.c
        include/opto7.h
)
add_library(Click.Opto7  ALIAS lib_opto7)



target_include_directories(lib_opto7 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_opto7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_opto7 PUBLIC MikroSDK.Driver)

