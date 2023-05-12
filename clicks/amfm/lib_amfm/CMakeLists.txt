cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_amfm LANGUAGES MikroC)
else()
    project(lib_amfm LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_amfm STATIC
        src/amfm.c
        include/amfm.h
)
add_library(Click.AmFm  ALIAS lib_amfm)



target_include_directories(lib_amfm PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_amfm PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_amfm PUBLIC MikroSDK.Driver)
