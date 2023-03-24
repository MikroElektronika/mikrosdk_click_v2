cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless17 LANGUAGES MikroC)
else()
    project(lib_brushless17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless17 STATIC
        src/brushless17.c
        include/brushless17.h
)
add_library(Click.Brushless17  ALIAS lib_brushless17)



target_include_directories(lib_brushless17 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless17 PUBLIC MikroSDK.Driver)
