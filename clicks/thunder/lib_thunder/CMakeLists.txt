cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thunder LANGUAGES MikroC)
else()
    project(lib_thunder LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thunder STATIC
        src/thunder.c
        include/thunder.h
)
add_library(Click.Thunder  ALIAS lib_thunder)



target_include_directories(lib_thunder PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thunder PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thunder PUBLIC MikroSDK.Driver)
