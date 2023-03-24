cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_environment2 LANGUAGES MikroC)
else()
    project(lib_environment2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_environment2 STATIC
        src/environment2.c
        include/environment2.h
)
add_library(Click.Environment2  ALIAS lib_environment2)



target_include_directories(lib_environment2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_environment2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_environment2 PUBLIC MikroSDK.Driver)
