cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_heartrate9 LANGUAGES MikroC)
else()
    project(lib_heartrate9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_heartrate9 STATIC
        src/heartrate9.c
        include/heartrate9.h
)
add_library(Click.HeartRate9  ALIAS lib_heartrate9)



target_include_directories(lib_heartrate9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_heartrate9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_heartrate9 PUBLIC MikroSDK.Driver)
