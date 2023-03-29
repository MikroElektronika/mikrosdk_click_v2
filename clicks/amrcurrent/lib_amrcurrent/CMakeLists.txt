cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_amrcurrent LANGUAGES MikroC)
else()
    project(lib_amrcurrent LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_amrcurrent STATIC
        src/amrcurrent.c
        include/amrcurrent.h
)
add_library(Click.AmrCurrent  ALIAS lib_amrcurrent)



target_include_directories(lib_amrcurrent PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_amrcurrent PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_amrcurrent PUBLIC MikroSDK.Driver)
