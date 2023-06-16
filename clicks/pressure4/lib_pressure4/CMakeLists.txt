cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure4 LANGUAGES MikroC)
else()
    project(lib_pressure4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure4 STATIC
        src/pressure4.c
        include/pressure4.h
)
add_library(Click.Pressure4  ALIAS lib_pressure4)



target_include_directories(lib_pressure4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure4 PUBLIC MikroSDK.Driver)
