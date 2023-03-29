cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c9dof2 LANGUAGES MikroC)
else()
    project(lib_c9dof2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c9dof2 STATIC
        src/c9dof2.c
        include/c9dof2.h
)
add_library(Click.9dof2  ALIAS lib_c9dof2)



target_include_directories(lib_c9dof2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c9dof2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c9dof2 PUBLIC MikroSDK.Driver)
