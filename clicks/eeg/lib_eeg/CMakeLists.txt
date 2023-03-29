cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eeg LANGUAGES MikroC)
else()
    project(lib_eeg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eeg STATIC
        src/eeg.c
        include/eeg.h
)
add_library(Click.EEG  ALIAS lib_eeg)



target_include_directories(lib_eeg PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eeg PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eeg PUBLIC MikroSDK.Driver)
