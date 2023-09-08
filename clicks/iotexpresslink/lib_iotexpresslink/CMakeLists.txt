cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_iotexpresslink LANGUAGES MikroC)
else()
    project(lib_iotexpresslink LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_iotexpresslink STATIC
        src/iotexpresslink.c
        include/iotexpresslink.h
)
add_library(Click.IoTExpressLink  ALIAS lib_iotexpresslink)



target_include_directories(lib_iotexpresslink PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_iotexpresslink PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_iotexpresslink PUBLIC MikroSDK.Driver)

