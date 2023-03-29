cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs4855 LANGUAGES MikroC)
else()
    project(lib_rs4855 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs4855 STATIC
        src/rs4855.c
        include/rs4855.h
)
add_library(Click.Rs4855  ALIAS lib_rs4855)



target_include_directories(lib_rs4855 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs4855 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs4855 PUBLIC MikroSDK.Driver)
