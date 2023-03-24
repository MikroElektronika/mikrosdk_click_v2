cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_co LANGUAGES MikroC)
else()
    project(lib_co LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_co STATIC
        src/co.c
        include/co.h
)
add_library(Click.CO  ALIAS lib_co)



target_include_directories(lib_co PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_co PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_co PUBLIC MikroSDK.Driver)
