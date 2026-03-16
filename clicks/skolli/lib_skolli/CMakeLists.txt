cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_skolli LANGUAGES MikroC)
else()
    project(lib_skolli LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_skolli STATIC
        src/skolli.c
        include/skolli.h
)
add_library(Click.SkollI  ALIAS lib_skolli)



target_include_directories(lib_skolli PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_skolli PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_skolli PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_skolli PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_skolli PUBLIC MikroSDK.GenericPointer)

