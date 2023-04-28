cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ldo LANGUAGES MikroC)
else()
    project(lib_ldo LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ldo STATIC
        src/ldo.c
        include/ldo.h
)
add_library(Click.LDO  ALIAS lib_ldo)



target_include_directories(lib_ldo PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ldo PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ldo PUBLIC MikroSDK.Driver)

