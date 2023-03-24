cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ozone3 LANGUAGES MikroC)
else()
    project(lib_ozone3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ozone3 STATIC
        src/ozone3.c
        include/ozone3.h
)
add_library(Click.Ozone3  ALIAS lib_ozone3)



target_include_directories(lib_ozone3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ozone3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ozone3 PUBLIC MikroSDK.Driver)
