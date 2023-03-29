cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c13dof LANGUAGES MikroC)
else()
    project(lib_c13dof LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c13dof STATIC
        src/c13dof.c
        include/c13dof.h
)
add_library(Click.13DOF  ALIAS lib_c13dof)



target_include_directories(lib_c13dof PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c13dof PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c13dof PUBLIC MikroSDK.Driver)
