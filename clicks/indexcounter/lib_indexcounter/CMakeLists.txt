cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_indexcounter LANGUAGES MikroC)
else()
    project(lib_indexcounter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_indexcounter STATIC
        src/indexcounter.c
        include/indexcounter.h
)
add_library(Click.IndexCounter  ALIAS lib_indexcounter)



target_include_directories(lib_indexcounter PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_indexcounter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_indexcounter PUBLIC MikroSDK.Driver)
