cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dac6 LANGUAGES MikroC)
else()
    project(lib_dac6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dac6 STATIC
        src/dac6.c
        include/dac6.h
)
add_library(Click.Dac6  ALIAS lib_dac6)



target_include_directories(lib_dac6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dac6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dac6 PUBLIC MikroSDK.Driver)
