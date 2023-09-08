cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_headphoneamp2 LANGUAGES MikroC)
else()
    project(lib_headphoneamp2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_headphoneamp2 STATIC
        src/headphoneamp2.c
        include/headphoneamp2.h
)
add_library(Click.HeadphoneAMP2  ALIAS lib_headphoneamp2)



target_include_directories(lib_headphoneamp2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_headphoneamp2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_headphoneamp2 PUBLIC MikroSDK.Driver)

