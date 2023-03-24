cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_touchkey LANGUAGES MikroC)
else()
    project(lib_touchkey LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_touchkey STATIC
        src/touchkey.c
        include/touchkey.h
)
add_library(Click.TouchKey  ALIAS lib_touchkey)



target_include_directories(lib_touchkey PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_touchkey PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_touchkey PUBLIC MikroSDK.Driver)
