cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_oximeter2 LANGUAGES MikroC)
else()
    project(lib_oximeter2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_oximeter2 STATIC
        src/oximeter2.c
        include/oximeter2.h
)
add_library(Click.Oximeter2  ALIAS lib_oximeter2)



target_include_directories(lib_oximeter2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_oximeter2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_oximeter2 PUBLIC MikroSDK.Driver)
