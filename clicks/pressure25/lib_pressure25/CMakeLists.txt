cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure25 LANGUAGES MikroC)
else()
    project(lib_pressure25 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure25 STATIC
        src/pressure25.c
        include/pressure25.h
)
add_library(Click.Pressure25  ALIAS lib_pressure25)



target_include_directories(lib_pressure25 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure25 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure25 PUBLIC MikroSDK.Driver)

