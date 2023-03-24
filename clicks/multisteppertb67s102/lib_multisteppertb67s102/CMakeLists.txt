cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_multisteppertb67s102 LANGUAGES MikroC)
else()
    project(lib_multisteppertb67s102 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_multisteppertb67s102 STATIC
        src/multisteppertb67s102.c
        include/multisteppertb67s102.h
)
add_library(Click.MultiStepperTB67S102  ALIAS lib_multisteppertb67s102)



target_include_directories(lib_multisteppertb67s102 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_multisteppertb67s102 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_multisteppertb67s102 PUBLIC MikroSDK.Driver)
