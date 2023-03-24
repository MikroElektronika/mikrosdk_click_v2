cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c7x10b LANGUAGES MikroC)
else()
    project(lib_c7x10b LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c7x10b STATIC
        src/c7x10b.c
        include/c7x10b.h    include/c7x10b_font.h
)
add_library(Click.7x10B  ALIAS lib_c7x10b)



target_include_directories(lib_c7x10b PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c7x10b PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c7x10b PUBLIC MikroSDK.Driver)
