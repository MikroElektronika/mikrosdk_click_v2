cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_comparator LANGUAGES MikroC)
else()
    project(lib_comparator LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_comparator STATIC
        src/comparator.c
        include/comparator.h
)
add_library(Click.Comparator  ALIAS lib_comparator)



target_include_directories(lib_comparator PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_comparator PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_comparator PUBLIC MikroSDK.Driver)
