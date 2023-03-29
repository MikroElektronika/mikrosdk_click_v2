cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_headphoneamp LANGUAGES MikroC)
else()
    project(lib_headphoneamp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_headphoneamp STATIC
        src/headphoneamp.c
        include/headphoneamp.h
)
add_library(Click.HeadphoneAMP  ALIAS lib_headphoneamp)



target_include_directories(lib_headphoneamp PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_headphoneamp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_headphoneamp PUBLIC MikroSDK.Driver)
