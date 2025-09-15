cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_smartbuck6 LANGUAGES MikroC)
else()
    project(lib_smartbuck6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_smartbuck6 STATIC
        src/smartbuck6.c
        include/smartbuck6.h
)
add_library(Click.SmartBuck6  ALIAS lib_smartbuck6)



target_include_directories(lib_smartbuck6 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_smartbuck6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_smartbuck6 PUBLIC MikroSDK.Driver)

