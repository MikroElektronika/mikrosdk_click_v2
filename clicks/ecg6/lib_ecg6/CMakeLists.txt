cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ecg6 LANGUAGES MikroC)
else()
    project(lib_ecg6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ecg6 STATIC
        src/ecg6.c
        include/ecg6.h
)
add_library(Click.Ecg6  ALIAS lib_ecg6)



target_include_directories(lib_ecg6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ecg6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ecg6 PUBLIC MikroSDK.Driver)
