cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c10dof LANGUAGES MikroC)
else()
    project(lib_c10dof LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c10dof STATIC
        src/c10dof.c
        include/c10dof.h
)
add_library(Click.10Dof  ALIAS lib_c10dof)



target_include_directories(lib_c10dof PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c10dof PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c10dof PUBLIC MikroSDK.Driver)
