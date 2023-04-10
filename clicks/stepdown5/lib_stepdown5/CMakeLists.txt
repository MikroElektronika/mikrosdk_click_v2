cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepdown5 LANGUAGES MikroC)
else()
    project(lib_stepdown5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepdown5 STATIC
        src/stepdown5.c
        include/stepdown5.h
)
add_library(Click.StepDown5  ALIAS lib_stepdown5)



target_include_directories(lib_stepdown5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepdown5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepdown5 PUBLIC MikroSDK.Driver)

