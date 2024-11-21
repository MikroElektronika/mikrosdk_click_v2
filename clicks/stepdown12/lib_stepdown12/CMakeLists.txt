cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepdown12 LANGUAGES MikroC)
else()
    project(lib_stepdown12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepdown12 STATIC
        src/stepdown12.c
        include/stepdown12.h
)
add_library(Click.StepDown12  ALIAS lib_stepdown12)



target_include_directories(lib_stepdown12 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepdown12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepdown12 PUBLIC MikroSDK.Driver)

