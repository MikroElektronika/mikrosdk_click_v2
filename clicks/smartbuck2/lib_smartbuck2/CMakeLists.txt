cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_smartbuck2 LANGUAGES MikroC)
else()
    project(lib_smartbuck2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_smartbuck2 STATIC
        src/smartbuck2.c
        include/smartbuck2.h
)
add_library(Click.SmartBuck2  ALIAS lib_smartbuck2)



target_include_directories(lib_smartbuck2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_smartbuck2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_smartbuck2 PUBLIC MikroSDK.Driver)

