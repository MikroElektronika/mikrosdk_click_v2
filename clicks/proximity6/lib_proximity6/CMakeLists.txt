cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity6 LANGUAGES MikroC)
else()
    project(lib_proximity6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity6 STATIC
        src/proximity6.c
        include/proximity6.h
)
add_library(Click.Proximity6  ALIAS lib_proximity6)



target_include_directories(lib_proximity6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity6 PUBLIC MikroSDK.Driver)
