cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_printer LANGUAGES MikroC)
else()
    project(lib_printer LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_printer STATIC
        src/printer.c
        include/printer.h
)
add_library(Click.Printer  ALIAS lib_printer)



target_include_directories(lib_printer PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_printer PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_printer PUBLIC MikroSDK.Driver)

