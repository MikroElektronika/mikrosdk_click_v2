cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_adac4 LANGUAGES MikroC)
else()
    project(lib_adac4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_adac4 STATIC
        src/adac4.c
        include/adac4.h
)
add_library(Click.ADAC4  ALIAS lib_adac4)



target_include_directories(lib_adac4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_adac4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_adac4 PUBLIC MikroSDK.Driver)

