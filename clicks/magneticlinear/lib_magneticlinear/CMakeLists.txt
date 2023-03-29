cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magneticlinear LANGUAGES MikroC)
else()
    project(lib_magneticlinear LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magneticlinear STATIC
        src/magneticlinear.c
        include/magneticlinear.h
)
add_library(Click.Magneticlinear  ALIAS lib_magneticlinear)



target_include_directories(lib_magneticlinear PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magneticlinear PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magneticlinear PUBLIC MikroSDK.Driver)
