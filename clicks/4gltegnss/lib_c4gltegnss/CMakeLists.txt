cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c4gltegnss LANGUAGES MikroC)
else()
    project(lib_c4gltegnss LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c4gltegnss STATIC
        src/c4gltegnss.c
        include/c4gltegnss.h
)
add_library(Click.4GLTEGNSS  ALIAS lib_c4gltegnss)



target_include_directories(lib_c4gltegnss PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c4gltegnss PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c4gltegnss PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c4gltegnss PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_c4gltegnss PUBLIC MikroSDK.GenericPointer)

