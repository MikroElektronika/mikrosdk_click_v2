cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ecg4 LANGUAGES MikroC)
else()
    project(lib_ecg4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ecg4 STATIC
        src/ecg4.c
        include/ecg4.h
)
add_library(Click.Ecg4  ALIAS lib_ecg4)



target_include_directories(lib_ecg4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ecg4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ecg4 PUBLIC MikroSDK.Driver)
