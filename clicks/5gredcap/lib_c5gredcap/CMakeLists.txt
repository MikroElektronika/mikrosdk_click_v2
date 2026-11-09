cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c5gredcap LANGUAGES MikroC)
else()
    project(lib_c5gredcap LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c5gredcap STATIC
        src/c5gredcap.c
        include/c5gredcap.h
)
add_library(Click.5GRedCap  ALIAS lib_c5gredcap)



target_include_directories(lib_c5gredcap PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c5gredcap PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c5gredcap PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c5gredcap PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_c5gredcap PUBLIC MikroSDK.GenericPointer)
