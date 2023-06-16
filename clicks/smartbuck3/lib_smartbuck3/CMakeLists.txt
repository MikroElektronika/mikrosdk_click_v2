cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_smartbuck3 LANGUAGES MikroC)
else()
    project(lib_smartbuck3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_smartbuck3 STATIC
        src/smartbuck3.c
        include/smartbuck3.h
)
add_library(Click.SmartBuck3  ALIAS lib_smartbuck3)



target_include_directories(lib_smartbuck3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_smartbuck3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_smartbuck3 PUBLIC MikroSDK.Driver)

