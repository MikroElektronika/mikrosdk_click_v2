cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_heartrate13 LANGUAGES MikroC)
else()
    project(lib_heartrate13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_heartrate13 STATIC
        src/heartrate13.c
        include/heartrate13.h
)
add_library(Click.HeartRate13  ALIAS lib_heartrate13)



target_include_directories(lib_heartrate13 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_heartrate13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_heartrate13 PUBLIC MikroSDK.Driver)

