cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_heartrate4 LANGUAGES MikroC)
else()
    project(lib_heartrate4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_heartrate4 STATIC
        src/heartrate4.c
        include/heartrate4.h
)
add_library(Click.HeartRate4  ALIAS lib_heartrate4)



target_include_directories(lib_heartrate4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_heartrate4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_heartrate4 PUBLIC MikroSDK.Driver)
