cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lighttemp LANGUAGES MikroC)
else()
    project(lib_lighttemp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lighttemp STATIC
        src/lighttemp.c
        include/lighttemp.h
)
add_library(Click.LightTemp  ALIAS lib_lighttemp)



target_include_directories(lib_lighttemp PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lighttemp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lighttemp PUBLIC MikroSDK.Driver)
