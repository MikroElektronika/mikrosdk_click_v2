cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c1wireswitch LANGUAGES MikroC)
else()
    project(lib_c1wireswitch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c1wireswitch STATIC
        src/c1wireswitch.c
        include/c1wireswitch.h
)
add_library(Click.c1WireSwitch  ALIAS lib_c1wireswitch)



target_include_directories(lib_c1wireswitch PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c1wireswitch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c1wireswitch PUBLIC MikroSDK.Driver)

