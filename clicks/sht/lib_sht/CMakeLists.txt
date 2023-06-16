cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_sht LANGUAGES MikroC)
else()
    project(lib_sht LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_sht STATIC
        src/sht.c
        include/sht.h
)
add_library(Click.Sht  ALIAS lib_sht)



target_include_directories(lib_sht PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_sht PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_sht PUBLIC MikroSDK.Driver)
