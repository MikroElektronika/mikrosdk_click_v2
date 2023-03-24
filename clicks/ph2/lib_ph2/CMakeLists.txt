cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ph2 LANGUAGES MikroC)
else()
    project(lib_ph2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ph2 STATIC
        src/ph2.c
        include/ph2.h
)
add_library(Click.pH2  ALIAS lib_ph2)



target_include_directories(lib_ph2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ph2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ph2 PUBLIC MikroSDK.Driver)

