cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ir LANGUAGES MikroC)
else()
    project(lib_ir LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ir STATIC
        src/ir.c
        include/ir.h
)
add_library(Click.IR  ALIAS lib_ir)



target_include_directories(lib_ir PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ir PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ir PUBLIC MikroSDK.Driver)
