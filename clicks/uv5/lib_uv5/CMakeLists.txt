cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uv5 LANGUAGES MikroC)
else()
    project(lib_uv5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uv5 STATIC
        src/uv5.c
        include/uv5.h
)
add_library(Click.UV5  ALIAS lib_uv5)



target_include_directories(lib_uv5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uv5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uv5 PUBLIC MikroSDK.Driver)

