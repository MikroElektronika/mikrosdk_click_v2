cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck7 LANGUAGES MikroC)
else()
    project(lib_buck7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck7 STATIC
        src/buck7.c
        include/buck7.h
)
add_library(Click.BUCK7  ALIAS lib_buck7)



target_include_directories(lib_buck7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck7 PUBLIC MikroSDK.Driver)
