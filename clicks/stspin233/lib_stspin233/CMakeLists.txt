cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stspin233 LANGUAGES MikroC)
else()
    project(lib_stspin233 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stspin233 STATIC
        src/stspin233.c
        include/stspin233.h
)
add_library(Click.Stspin233  ALIAS lib_stspin233)



target_include_directories(lib_stspin233 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stspin233 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stspin233 PUBLIC MikroSDK.Driver)
