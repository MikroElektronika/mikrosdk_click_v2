cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c9dof LANGUAGES MikroC)
else()
    project(lib_c9dof LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c9dof STATIC
        src/c9dof.c
        include/c9dof.h
)
add_library(Click.9Dof  ALIAS lib_c9dof)



target_include_directories(lib_c9dof PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c9dof PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c9dof PUBLIC MikroSDK.Driver)
