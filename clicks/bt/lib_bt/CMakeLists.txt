cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bt LANGUAGES MikroC)
else()
    project(lib_bt LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bt STATIC
        src/bt.c
        include/bt.h
)
add_library(Click.BT  ALIAS lib_bt)



target_include_directories(lib_bt PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bt PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bt PUBLIC MikroSDK.Driver)
