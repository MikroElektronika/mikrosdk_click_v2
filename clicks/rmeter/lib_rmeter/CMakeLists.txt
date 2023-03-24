cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rmeter LANGUAGES MikroC)
else()
    project(lib_rmeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rmeter STATIC
        src/rmeter.c
        include/rmeter.h
)
add_library(Click.Rmeter  ALIAS lib_rmeter)



target_include_directories(lib_rmeter PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rmeter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rmeter PUBLIC MikroSDK.Driver)
