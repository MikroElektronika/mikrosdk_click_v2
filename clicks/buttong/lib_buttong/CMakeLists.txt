cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buttong LANGUAGES MikroC)
else()
    project(lib_buttong LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buttong STATIC
        src/buttong.c
        include/buttong.h
)
add_library(Click.ButtonG  ALIAS lib_buttong)



target_include_directories(lib_buttong PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buttong PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buttong PUBLIC MikroSDK.Driver)
