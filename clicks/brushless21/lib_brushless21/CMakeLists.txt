cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless21 LANGUAGES MikroC)
else()
    project(lib_brushless21 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless21 STATIC
        src/brushless21.c
        include/brushless21.h
)
add_library(Click.Brushless21  ALIAS lib_brushless21)



target_include_directories(lib_brushless21 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless21 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless21 PUBLIC MikroSDK.Driver)
