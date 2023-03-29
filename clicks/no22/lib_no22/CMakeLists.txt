cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_no22 LANGUAGES MikroC)
else()
    project(lib_no22 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_no22 STATIC
        src/no22.c
        include/no22.h
)
add_library(Click.NO22  ALIAS lib_no22)



target_include_directories(lib_no22 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_no22 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_no22 PUBLIC MikroSDK.Driver)
