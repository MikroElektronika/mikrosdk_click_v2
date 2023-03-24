cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hbridgedriver LANGUAGES MikroC)
else()
    project(lib_hbridgedriver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hbridgedriver STATIC
        src/hbridgedriver.c
        include/hbridgedriver.h
)
add_library(Click.HBridgeDriver  ALIAS lib_hbridgedriver)



target_include_directories(lib_hbridgedriver PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hbridgedriver PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hbridgedriver PUBLIC MikroSDK.Driver)
