cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_force5 LANGUAGES MikroC)
else()
    project(lib_force5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_force5 STATIC
        src/force5.c
        include/force5.h
)
add_library(Click.Force5  ALIAS lib_force5)



target_include_directories(lib_force5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_force5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_force5 PUBLIC MikroSDK.Driver)
