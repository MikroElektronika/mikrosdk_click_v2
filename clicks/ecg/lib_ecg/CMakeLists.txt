cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ecg LANGUAGES MikroC)
else()
    project(lib_ecg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ecg STATIC
        src/ecg.c
        include/ecg.h
)
add_library(Click.Ecg  ALIAS lib_ecg)



target_include_directories(lib_ecg PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ecg PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ecg PUBLIC MikroSDK.Driver)
