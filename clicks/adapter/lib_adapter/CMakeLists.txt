cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_adapter LANGUAGES MikroC)
else()
    project(lib_adapter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_adapter STATIC
        src/adapter.c
        include/adapter.h
)
add_library(Click.Adapter  ALIAS lib_adapter)



target_include_directories(lib_adapter PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_adapter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_adapter PUBLIC MikroSDK.Driver)
