cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magaccel LANGUAGES MikroC)
else()
    project(lib_magaccel LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magaccel STATIC
        src/magaccel.c
        include/magaccel.h
)
add_library(Click.MagAccel  ALIAS lib_magaccel)



target_include_directories(lib_magaccel PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magaccel PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magaccel PUBLIC MikroSDK.Driver)

