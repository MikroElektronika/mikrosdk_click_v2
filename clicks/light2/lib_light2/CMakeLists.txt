cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_light2 LANGUAGES MikroC)
else()
    project(lib_light2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_light2 STATIC
        src/light2.c
        include/light2.h
)
add_library(Click.Light2  ALIAS lib_light2)



target_include_directories(lib_light2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_light2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_light2 PUBLIC MikroSDK.Driver)

