cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rfswitch LANGUAGES MikroC)
else()
    project(lib_rfswitch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rfswitch STATIC
        src/rfswitch.c
        include/rfswitch.h
)
add_library(Click.RFSwitch  ALIAS lib_rfswitch)



target_include_directories(lib_rfswitch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rfswitch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rfswitch PUBLIC MikroSDK.Driver)
