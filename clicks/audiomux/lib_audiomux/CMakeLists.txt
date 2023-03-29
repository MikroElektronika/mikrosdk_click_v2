cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_audiomux LANGUAGES MikroC)
else()
    project(lib_audiomux LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_audiomux STATIC
        src/audiomux.c
        include/audiomux.h
)
add_library(Click.AudioMUX  ALIAS lib_audiomux)



target_include_directories(lib_audiomux PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_audiomux PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_audiomux PUBLIC MikroSDK.Driver)
