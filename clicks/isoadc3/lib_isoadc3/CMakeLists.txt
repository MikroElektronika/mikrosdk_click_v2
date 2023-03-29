cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_isoadc3 LANGUAGES MikroC)
else()
    project(lib_isoadc3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_isoadc3 STATIC
        src/isoadc3.c
        include/isoadc3.h
)
add_library(Click.ISOADC3  ALIAS lib_isoadc3)



target_include_directories(lib_isoadc3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_isoadc3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_isoadc3 PUBLIC MikroSDK.Driver)
