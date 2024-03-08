cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stspin820 LANGUAGES MikroC)
else()
    project(lib_stspin820 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stspin820 STATIC
        src/stspin820.c
        include/stspin820.h
)
add_library(Click.STSPIN820  ALIAS lib_stspin820)



target_include_directories(lib_stspin820 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stspin820 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stspin820 PUBLIC MikroSDK.Driver)

