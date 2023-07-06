cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thingstream LANGUAGES MikroC)
else()
    project(lib_thingstream LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thingstream STATIC
        src/thingstream.c
        include/thingstream.h
)
add_library(Click.Thingstream  ALIAS lib_thingstream)



target_include_directories(lib_thingstream PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thingstream PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thingstream PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_thingstream PUBLIC MikroSDK.GenericPointer)
