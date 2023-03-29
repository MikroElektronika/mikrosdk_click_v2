cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient5 LANGUAGES MikroC)
else()
    project(lib_ambient5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient5 STATIC
        src/ambient5.c
        include/ambient5.h
)
add_library(Click.Ambient5  ALIAS lib_ambient5)



target_include_directories(lib_ambient5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient5 PUBLIC MikroSDK.Driver)
