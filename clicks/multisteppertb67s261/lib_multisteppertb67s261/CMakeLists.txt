cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_multisteppertb67s261 LANGUAGES MikroC)
else()
    project(lib_multisteppertb67s261 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_multisteppertb67s261 STATIC
        src/multisteppertb67s261.c
        include/multisteppertb67s261.h
)
add_library(Click.MultiStepperTB67S261  ALIAS lib_multisteppertb67s261)



target_include_directories(lib_multisteppertb67s261 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_multisteppertb67s261 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_multisteppertb67s261 PUBLIC MikroSDK.Driver)
