cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_motion LANGUAGES MikroC)
else()
    project(lib_motion LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_motion STATIC
        src/motion.c
        include/motion.h
)
add_library(Click.Motion  ALIAS lib_motion)



target_include_directories(lib_motion PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_motion PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_motion PUBLIC MikroSDK.Driver)
