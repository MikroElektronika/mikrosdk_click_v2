cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magneto6 LANGUAGES MikroC)
else()
    project(lib_magneto6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magneto6 STATIC
        src/magneto6.c
        include/magneto6.h
)
add_library(Click.Magneto6  ALIAS lib_magneto6)



target_include_directories(lib_magneto6 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magneto6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magneto6 PUBLIC MikroSDK.Driver)

