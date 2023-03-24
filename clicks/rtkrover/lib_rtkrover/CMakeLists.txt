cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rtkrover LANGUAGES MikroC)
else()
    project(lib_rtkrover LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rtkrover STATIC
        src/rtkrover.c
        include/rtkrover.h
)
add_library(Click.RTKRover  ALIAS lib_rtkrover)



target_include_directories(lib_rtkrover PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rtkrover PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rtkrover PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_rtkrover PUBLIC MikroSDK.GenericPointer)
