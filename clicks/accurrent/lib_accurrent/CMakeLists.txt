cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accurrent LANGUAGES MikroC)
else()
    project(lib_accurrent LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accurrent STATIC
        src/accurrent.c
        include/accurrent.h
)
add_library(Click.AcCurrent  ALIAS lib_accurrent)



target_include_directories(lib_accurrent PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accurrent PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accurrent PUBLIC MikroSDK.Driver)
