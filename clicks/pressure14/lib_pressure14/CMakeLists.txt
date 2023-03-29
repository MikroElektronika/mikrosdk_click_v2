cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure14 LANGUAGES MikroC)
else()
    project(lib_pressure14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure14 STATIC
        src/pressure14.c
        include/pressure14.h
)
add_library(Click.Pressure14  ALIAS lib_pressure14)



target_include_directories(lib_pressure14 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure14 PUBLIC MikroSDK.Driver)
