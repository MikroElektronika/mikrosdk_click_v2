cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_smartbuck LANGUAGES MikroC)
else()
    project(lib_smartbuck LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_smartbuck STATIC
        src/smartbuck.c
        include/smartbuck.h
)
add_library(Click.SMARTBUCK  ALIAS lib_smartbuck)



target_include_directories(lib_smartbuck PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_smartbuck PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_smartbuck PUBLIC MikroSDK.Driver)
