cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_canfd7 LANGUAGES MikroC)
else()
    project(lib_canfd7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_canfd7 STATIC
        src/canfd7.c
        include/canfd7.h
)
add_library(Click.CANFD7  ALIAS lib_canfd7)



target_include_directories(lib_canfd7 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_canfd7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_canfd7 PUBLIC MikroSDK.Driver)

