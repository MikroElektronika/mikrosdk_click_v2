cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepup LANGUAGES MikroC)
else()
    project(lib_stepup LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepup STATIC
        src/stepup.c
        include/stepup.h
)
add_library(Click.StepUp  ALIAS lib_stepup)



target_include_directories(lib_stepup PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepup PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepup PUBLIC MikroSDK.Driver)
