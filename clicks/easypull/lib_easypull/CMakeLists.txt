cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_easypull LANGUAGES MikroC)
else()
    project(lib_easypull LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_easypull STATIC
        src/easypull.c
        include/easypull.h
)
add_library(Click.EasyPull  ALIAS lib_easypull)



target_include_directories(lib_easypull PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_easypull PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_easypull PUBLIC MikroSDK.Driver)

