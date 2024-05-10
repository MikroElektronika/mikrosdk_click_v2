cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_cooler LANGUAGES MikroC)
else()
    project(lib_cooler LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_cooler STATIC
        src/cooler.c
        include/cooler.h
)
add_library(Click.Cooler  ALIAS lib_cooler)



target_include_directories(lib_cooler PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_cooler PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_cooler PUBLIC MikroSDK.Driver)

