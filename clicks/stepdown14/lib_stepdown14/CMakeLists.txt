cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepdown14 LANGUAGES MikroC)
else()
    project(lib_stepdown14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepdown14 STATIC
        src/stepdown14.c
        include/stepdown14.h
)
add_library(Click.StepDown14  ALIAS lib_stepdown14)



target_include_directories(lib_stepdown14 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepdown14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepdown14 PUBLIC MikroSDK.Driver)

