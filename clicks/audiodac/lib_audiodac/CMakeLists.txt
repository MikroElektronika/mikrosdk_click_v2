cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_audiodac LANGUAGES MikroC)
else()
    project(lib_audiodac LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_audiodac STATIC
        src/audiodac.c
        include/audiodac.h
)
add_library(Click.AudioDAC  ALIAS lib_audiodac)



target_include_directories(lib_audiodac PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_audiodac PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_audiodac PUBLIC MikroSDK.Driver)

