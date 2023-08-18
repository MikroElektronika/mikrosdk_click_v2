cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_clickid LANGUAGES MikroC)
else()
    project(lib_clickid LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_clickid STATIC
        src/clickid.c
        include/clickid.h
)
add_library(Click.ClickID  ALIAS lib_clickid)



target_include_directories(lib_clickid PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_clickid PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_clickid PUBLIC MikroSDK.Driver)

