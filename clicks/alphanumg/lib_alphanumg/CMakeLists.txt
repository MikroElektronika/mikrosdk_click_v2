cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_alphanumg LANGUAGES MikroC)
else()
    project(lib_alphanumg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_alphanumg STATIC
        src/alphanumg.c
        include/alphanumg.h
)
add_library(Click.AlphaNumG  ALIAS lib_alphanumg)



target_include_directories(lib_alphanumg PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_alphanumg PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_alphanumg PUBLIC MikroSDK.Driver)
