cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_fiberopt LANGUAGES MikroC)
else()
    project(lib_fiberopt LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_fiberopt STATIC
        src/fiberopt.c
        include/fiberopt.h
)
add_library(Click.FiberOpt  ALIAS lib_fiberopt)



target_include_directories(lib_fiberopt PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_fiberopt PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_fiberopt PUBLIC MikroSDK.Driver)
