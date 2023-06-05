cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper21 LANGUAGES MikroC)
else()
    project(lib_stepper21 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper21 STATIC
        src/stepper21.c
        include/stepper21.h
)
add_library(Click.Stepper21  ALIAS lib_stepper21)



target_include_directories(lib_stepper21 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper21 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper21 PUBLIC MikroSDK.Driver)

