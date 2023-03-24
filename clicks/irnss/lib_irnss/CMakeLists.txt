cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irnss LANGUAGES MikroC)
else()
    project(lib_irnss LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irnss STATIC
        src/irnss.c
        include/irnss.h
)
add_library(Click.IRNSS  ALIAS lib_irnss)



target_include_directories(lib_irnss PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irnss PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irnss PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_irnss PUBLIC MikroSDK.GenericPointer)
