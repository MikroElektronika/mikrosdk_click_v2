cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stspin220 LANGUAGES MikroC)
else()
    project(lib_stspin220 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stspin220 STATIC
        src/stspin220.c
        include/stspin220.h
)
add_library(Click.STSPIN220  ALIAS lib_stspin220)



target_include_directories(lib_stspin220 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stspin220 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stspin220 PUBLIC MikroSDK.Driver)

