cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rak11720 LANGUAGES MikroC)
else()
    project(lib_rak11720 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rak11720 STATIC
        src/rak11720.c
        include/rak11720.h
)
add_library(Click.RAK11720  ALIAS lib_rak11720)



target_include_directories(lib_rak11720 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rak11720 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rak11720 PUBLIC MikroSDK.Driver)

