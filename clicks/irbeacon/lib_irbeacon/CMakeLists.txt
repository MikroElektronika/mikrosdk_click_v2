cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irbeacon LANGUAGES MikroC)
else()
    project(lib_irbeacon LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irbeacon STATIC
        src/irbeacon.c
        include/irbeacon.h
)
add_library(Click.IrBeacon  ALIAS lib_irbeacon)



target_include_directories(lib_irbeacon PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irbeacon PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irbeacon PUBLIC MikroSDK.Driver)
