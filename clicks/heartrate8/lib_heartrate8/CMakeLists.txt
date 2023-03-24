cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_heartrate8 LANGUAGES MikroC)
else()
    project(lib_heartrate8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_heartrate8 STATIC
        src/heartrate8.c
        include/heartrate8.h
)
add_library(Click.HeartRate8  ALIAS lib_heartrate8)



target_include_directories(lib_heartrate8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_heartrate8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_heartrate8 PUBLIC MikroSDK.Driver)
