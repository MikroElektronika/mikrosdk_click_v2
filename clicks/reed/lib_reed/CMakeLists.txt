cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_reed LANGUAGES MikroC)
else()
    project(lib_reed LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_reed STATIC
        src/reed.c
        include/reed.h
)
add_library(Click.Reed  ALIAS lib_reed)



target_include_directories(lib_reed PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_reed PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_reed PUBLIC MikroSDK.Driver)
