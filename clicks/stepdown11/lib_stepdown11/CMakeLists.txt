cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepdown11 LANGUAGES MikroC)
else()
    project(lib_stepdown11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepdown11 STATIC
        src/stepdown11.c
        include/stepdown11.h
)
add_library(Click.StepDown11  ALIAS lib_stepdown11)



target_include_directories(lib_stepdown11 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepdown11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepdown11 PUBLIC MikroSDK.Driver)

