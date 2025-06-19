cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_xportethse LANGUAGES MikroC)
else()
    project(lib_xportethse LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_xportethse STATIC
        src/xportethse.c
        include/xportethse.h
)
add_library(Click.XPortETHSE  ALIAS lib_xportethse)



target_include_directories(lib_xportethse PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_xportethse PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_xportethse PUBLIC MikroSDK.Driver)

