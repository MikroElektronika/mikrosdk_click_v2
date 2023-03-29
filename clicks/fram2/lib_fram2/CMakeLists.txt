cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_fram2 LANGUAGES MikroC)
else()
    project(lib_fram2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_fram2 STATIC
        src/fram2.c
        include/fram2.h
)
add_library(Click.Fram2  ALIAS lib_fram2)



target_include_directories(lib_fram2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_fram2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_fram2 PUBLIC MikroSDK.Driver)
