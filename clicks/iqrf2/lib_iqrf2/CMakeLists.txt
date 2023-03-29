cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_iqrf2 LANGUAGES MikroC)
else()
    project(lib_iqrf2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_iqrf2 STATIC
        src/iqrf2.c
        include/iqrf2.h
)
add_library(Click.iqrf2  ALIAS lib_iqrf2)



target_include_directories(lib_iqrf2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_iqrf2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_iqrf2 PUBLIC MikroSDK.Driver)
