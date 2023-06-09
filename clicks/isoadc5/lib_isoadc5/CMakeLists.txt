cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_isoadc5 LANGUAGES MikroC)
else()
    project(lib_isoadc5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_isoadc5 STATIC
        src/isoadc5.c
        include/isoadc5.h
)
add_library(Click.ISOADC5  ALIAS lib_isoadc5)



target_include_directories(lib_isoadc5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_isoadc5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_isoadc5 PUBLIC MikroSDK.Driver)
