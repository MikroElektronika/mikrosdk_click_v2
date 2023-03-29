cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_radiostation LANGUAGES MikroC)
else()
    project(lib_radiostation LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_radiostation STATIC
        src/radiostation.c
        include/radiostation.h
)
add_library(Click.RadioStation  ALIAS lib_radiostation)



target_include_directories(lib_radiostation PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_radiostation PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_radiostation PUBLIC MikroSDK.Driver)
