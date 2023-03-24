cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_force3 LANGUAGES MikroC)
else()
    project(lib_force3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_force3 STATIC
        src/force3.c
        include/force3.h
)
add_library(Click.Force3  ALIAS lib_force3)



target_include_directories(lib_force3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_force3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_force3 PUBLIC MikroSDK.Driver)
