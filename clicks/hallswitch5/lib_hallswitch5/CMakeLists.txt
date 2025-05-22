cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallswitch5 LANGUAGES MikroC)
else()
    project(lib_hallswitch5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallswitch5 STATIC
        src/hallswitch5.c
        include/hallswitch5.h
)
add_library(Click.HallSwitch5  ALIAS lib_hallswitch5)



target_include_directories(lib_hallswitch5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallswitch5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallswitch5 PUBLIC MikroSDK.Driver)

