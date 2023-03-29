cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_audioxover LANGUAGES MikroC)
else()
    project(lib_audioxover LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_audioxover STATIC
        src/audioxover.c
        include/audioxover.h
)
add_library(Click.AudioXover  ALIAS lib_audioxover)



target_include_directories(lib_audioxover PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_audioxover PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_audioxover PUBLIC MikroSDK.Driver)
