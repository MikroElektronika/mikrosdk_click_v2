cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallswitch2 LANGUAGES MikroC)
else()
    project(lib_hallswitch2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallswitch2 STATIC
        src/hallswitch2.c
        include/hallswitch2.h
)
add_library(Click.HallSwitch2  ALIAS lib_hallswitch2)



target_include_directories(lib_hallswitch2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallswitch2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallswitch2 PUBLIC MikroSDK.Driver)
