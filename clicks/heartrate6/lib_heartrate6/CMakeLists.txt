cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_heartrate6 LANGUAGES MikroC)
else()
    project(lib_heartrate6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_heartrate6 STATIC
        src/heartrate6.c
        include/heartrate6.h
)
add_library(Click.HeartRate6  ALIAS lib_heartrate6)



target_include_directories(lib_heartrate6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_heartrate6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_heartrate6 PUBLIC MikroSDK.Driver)
