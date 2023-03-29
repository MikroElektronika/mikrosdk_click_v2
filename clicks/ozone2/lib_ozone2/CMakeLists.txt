cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ozone2 LANGUAGES MikroC)
else()
    project(lib_ozone2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ozone2 STATIC
        src/ozone2.c
        include/ozone2.h
)
add_library(Click.Ozone2  ALIAS lib_ozone2)



target_include_directories(lib_ozone2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ozone2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ozone2 PUBLIC MikroSDK.Driver)
