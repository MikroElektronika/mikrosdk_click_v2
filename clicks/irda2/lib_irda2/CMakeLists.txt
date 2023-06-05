cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irda2 LANGUAGES MikroC)
else()
    project(lib_irda2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irda2 STATIC
        src/irda2.c
        include/irda2.h
)
add_library(Click.IrDA2  ALIAS lib_irda2)



target_include_directories(lib_irda2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irda2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irda2 PUBLIC MikroSDK.Driver)
