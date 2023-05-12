cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_heartrate11 LANGUAGES MikroC)
else()
    project(lib_heartrate11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_heartrate11 STATIC
        src/heartrate11.c
        include/heartrate11.h
)
add_library(Click.HeartRate11  ALIAS lib_heartrate11)



target_include_directories(lib_heartrate11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_heartrate11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_heartrate11 PUBLIC MikroSDK.Driver)
