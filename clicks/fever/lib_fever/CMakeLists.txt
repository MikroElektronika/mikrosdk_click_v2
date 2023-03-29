cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_fever LANGUAGES MikroC)
else()
    project(lib_fever LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_fever STATIC
        src/fever.c
        include/fever.h
)
add_library(Click.Fever  ALIAS lib_fever)



target_include_directories(lib_fever PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_fever PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_fever PUBLIC MikroSDK.Driver)
