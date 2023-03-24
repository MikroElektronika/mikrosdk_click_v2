cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck19 LANGUAGES MikroC)
else()
    project(lib_buck19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck19 STATIC
        src/buck19.c
        include/buck19.h
)
add_library(Click.Buck19  ALIAS lib_buck19)



target_include_directories(lib_buck19 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck19 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck19 PUBLIC MikroSDK.Driver)
