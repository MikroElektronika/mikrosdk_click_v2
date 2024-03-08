cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_aiwb212f LANGUAGES MikroC)
else()
    project(lib_aiwb212f LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_aiwb212f STATIC
        src/aiwb212f.c
        include/aiwb212f.h
)
add_library(Click.AiWB212F  ALIAS lib_aiwb212f)



target_include_directories(lib_aiwb212f PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_aiwb212f PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_aiwb212f PUBLIC MikroSDK.Driver)

