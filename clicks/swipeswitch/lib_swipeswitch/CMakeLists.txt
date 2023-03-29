cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_swipeswitch LANGUAGES MikroC)
else()
    project(lib_swipeswitch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_swipeswitch STATIC
        src/swipeswitch.c
        include/swipeswitch.h
)
add_library(Click.SwipeSwitch  ALIAS lib_swipeswitch)



target_include_directories(lib_swipeswitch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_swipeswitch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_swipeswitch PUBLIC MikroSDK.Driver)
