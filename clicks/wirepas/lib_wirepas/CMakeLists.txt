cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_wirepas LANGUAGES MikroC)
else()
    project(lib_wirepas LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_wirepas STATIC
        src/wirepas.c
        include/wirepas.h
)
add_library(Click.Wirepas  ALIAS lib_wirepas)



target_include_directories(lib_wirepas PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_wirepas PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_wirepas PUBLIC MikroSDK.Driver)

