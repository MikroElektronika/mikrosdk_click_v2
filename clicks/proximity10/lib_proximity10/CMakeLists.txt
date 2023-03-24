cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity10 LANGUAGES MikroC)
else()
    project(lib_proximity10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity10 STATIC
        src/proximity10.c
        include/proximity10.h
)
add_library(Click.Proximity10  ALIAS lib_proximity10)



target_include_directories(lib_proximity10 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity10 PUBLIC MikroSDK.Driver)
