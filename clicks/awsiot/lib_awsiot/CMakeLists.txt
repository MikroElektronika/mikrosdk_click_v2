cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_awsiot LANGUAGES MikroC)
else()
    project(lib_awsiot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_awsiot STATIC
        src/awsiot.c
        include/awsiot.h
)
add_library(Click.AWSIoT  ALIAS lib_awsiot)



target_include_directories(lib_awsiot PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_awsiot PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_awsiot PUBLIC MikroSDK.Driver)

