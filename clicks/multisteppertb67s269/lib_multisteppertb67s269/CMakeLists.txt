cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_multisteppertb67s269 LANGUAGES MikroC)
else()
    project(lib_multisteppertb67s269 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_multisteppertb67s269 STATIC
        src/multisteppertb67s269.c
        include/multisteppertb67s269.h
)
add_library(Click.MultiStepperTB67S269  ALIAS lib_multisteppertb67s269)



target_include_directories(lib_multisteppertb67s269 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_multisteppertb67s269 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_multisteppertb67s269 PUBLIC MikroSDK.Driver)
