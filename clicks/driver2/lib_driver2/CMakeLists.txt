cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_driver2 LANGUAGES MikroC)
else()
    project(lib_driver2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_driver2 STATIC
        src/driver2.c
        include/driver2.h
)
add_library(Click.Driver2  ALIAS lib_driver2)



target_include_directories(lib_driver2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_driver2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_driver2 PUBLIC MikroSDK.Driver)
