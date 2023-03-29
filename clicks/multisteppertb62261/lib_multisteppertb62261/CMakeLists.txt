cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_multisteppertb62261 LANGUAGES MikroC)
else()
    project(lib_multisteppertb62261 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_multisteppertb62261 STATIC
        src/multisteppertb62261.c
        include/multisteppertb62261.h
)
add_library(Click.MultiStepperTB62261  ALIAS lib_multisteppertb62261)



target_include_directories(lib_multisteppertb62261 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_multisteppertb62261 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_multisteppertb62261 PUBLIC MikroSDK.Driver)
