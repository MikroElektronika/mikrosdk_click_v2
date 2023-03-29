cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs4853v3 LANGUAGES MikroC)
else()
    project(lib_rs4853v3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs4853v3 STATIC
        src/rs4853v3.c
        include/rs4853v3.h
)
add_library(Click.RS4853V3  ALIAS lib_rs4853v3)



target_include_directories(lib_rs4853v3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs4853v3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs4853v3 PUBLIC MikroSDK.Driver)
