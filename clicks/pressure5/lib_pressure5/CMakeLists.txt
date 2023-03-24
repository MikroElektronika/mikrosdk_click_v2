cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure5 LANGUAGES MikroC)
else()
    project(lib_pressure5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure5 STATIC
        src/pressure5.c
        include/pressure5.h
)
add_library(Click.Pressure5  ALIAS lib_pressure5)



target_include_directories(lib_pressure5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure5 PUBLIC MikroSDK.Driver)
