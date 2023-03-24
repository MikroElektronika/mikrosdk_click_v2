cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless7 LANGUAGES MikroC)
else()
    project(lib_brushless7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless7 STATIC
        src/brushless7.c
        include/brushless7.h
)
add_library(Click.Brushless7  ALIAS lib_brushless7)



target_include_directories(lib_brushless7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless7 PUBLIC MikroSDK.Driver)
