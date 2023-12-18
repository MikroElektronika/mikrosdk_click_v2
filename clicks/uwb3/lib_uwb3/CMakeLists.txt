cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uwb3 LANGUAGES MikroC)
else()
    project(lib_uwb3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uwb3 STATIC
        src/uwb3.c
        include/uwb3.h
)
add_library(Click.UWB3  ALIAS lib_uwb3)



target_include_directories(lib_uwb3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uwb3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uwb3 PUBLIC MikroSDK.Driver)

