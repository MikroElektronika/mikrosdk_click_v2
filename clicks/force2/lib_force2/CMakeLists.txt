cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_force2 LANGUAGES MikroC)
else()
    project(lib_force2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_force2 STATIC
        src/force2.c
        include/force2.h
)
add_library(Click.Force2  ALIAS lib_force2)



target_include_directories(lib_force2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_force2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_force2 PUBLIC MikroSDK.Driver)
