cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ltecat1us LANGUAGES MikroC)
else()
    project(lib_ltecat1us LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ltecat1us STATIC
        src/ltecat1us.c
        include/ltecat1us.h
)
add_library(Click.LTECat1US  ALIAS lib_ltecat1us)



target_include_directories(lib_ltecat1us PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ltecat1us PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ltecat1us PUBLIC MikroSDK.Driver)
