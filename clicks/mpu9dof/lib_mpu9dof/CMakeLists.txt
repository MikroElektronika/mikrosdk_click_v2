cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mpu9dof LANGUAGES MikroC)
else()
    project(lib_mpu9dof LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mpu9dof STATIC
        src/mpu9dof.c
        include/mpu9dof.h
)
add_library(Click.Mpu9Dof  ALIAS lib_mpu9dof)



target_include_directories(lib_mpu9dof PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mpu9dof PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mpu9dof PUBLIC MikroSDK.Driver)
