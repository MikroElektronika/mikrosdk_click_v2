cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_headphoneamp3 LANGUAGES MikroC)
else()
    project(lib_headphoneamp3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_headphoneamp3 STATIC
        src/headphoneamp3.c
        include/headphoneamp3.h
)
add_library(Click.HeadphomeAMP3  ALIAS lib_headphoneamp3)



target_include_directories(lib_headphoneamp3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_headphoneamp3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_headphoneamp3 PUBLIC MikroSDK.Driver)

