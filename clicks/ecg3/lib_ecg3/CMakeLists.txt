cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ecg3 LANGUAGES MikroC)
else()
    project(lib_ecg3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ecg3 STATIC
        src/ecg3.c
        include/ecg3.h
)
add_library(Click.Ecg3  ALIAS lib_ecg3)



target_include_directories(lib_ecg3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ecg3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ecg3 PUBLIC MikroSDK.Driver)
