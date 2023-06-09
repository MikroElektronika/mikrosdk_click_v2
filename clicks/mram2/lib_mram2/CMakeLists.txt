cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mram2 LANGUAGES MikroC)
else()
    project(lib_mram2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mram2 STATIC
        src/mram2.c
        include/mram2.h
)
add_library(Click.Mram2  ALIAS lib_mram2)



target_include_directories(lib_mram2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mram2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mram2 PUBLIC MikroSDK.Driver)
