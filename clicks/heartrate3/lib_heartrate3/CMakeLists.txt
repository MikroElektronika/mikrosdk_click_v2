cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_heartrate3 LANGUAGES MikroC)
else()
    project(lib_heartrate3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_heartrate3 STATIC
        src/heartrate3.c
        include/heartrate3.h
)
add_library(Click.HeartRate3  ALIAS lib_heartrate3)



target_include_directories(lib_heartrate3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_heartrate3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_heartrate3 PUBLIC MikroSDK.Driver)
