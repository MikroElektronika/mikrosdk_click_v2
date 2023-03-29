cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irgesture LANGUAGES MikroC)
else()
    project(lib_irgesture LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irgesture STATIC
        src/irgesture.c
        include/irgesture.h
)
add_library(Click.IrGesture  ALIAS lib_irgesture)



target_include_directories(lib_irgesture PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irgesture PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irgesture PUBLIC MikroSDK.Driver)
