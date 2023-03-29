cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ireclipse LANGUAGES MikroC)
else()
    project(lib_ireclipse LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ireclipse STATIC
        src/ireclipse.c
        include/ireclipse.h
)
add_library(Click.IrEclipse  ALIAS lib_ireclipse)



target_include_directories(lib_ireclipse PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ireclipse PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ireclipse PUBLIC MikroSDK.Driver)
