cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_emg LANGUAGES MikroC)
else()
    project(lib_emg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_emg STATIC
        src/emg.c
        include/emg.h
)
add_library(Click.EMG  ALIAS lib_emg)



target_include_directories(lib_emg PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_emg PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_emg PUBLIC MikroSDK.Driver)
