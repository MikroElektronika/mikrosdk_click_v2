cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_turbidity LANGUAGES MikroC)
else()
    project(lib_turbidity LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_turbidity STATIC
        src/turbidity.c
        include/turbidity.h
)
add_library(Click.Turbidity  ALIAS lib_turbidity)



target_include_directories(lib_turbidity PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_turbidity PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_turbidity PUBLIC MikroSDK.Driver)
