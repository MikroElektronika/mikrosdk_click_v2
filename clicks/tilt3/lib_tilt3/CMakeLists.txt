cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tilt3 LANGUAGES MikroC)
else()
    project(lib_tilt3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tilt3 STATIC
        src/tilt3.c
        include/tilt3.h
)
add_library(Click.Tilt3  ALIAS lib_tilt3)



target_include_directories(lib_tilt3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tilt3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tilt3 PUBLIC MikroSDK.Driver)
