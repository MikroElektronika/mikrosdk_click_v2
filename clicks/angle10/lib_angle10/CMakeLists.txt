cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_angle10 LANGUAGES MikroC)
else()
    project(lib_angle10 LANGUAGES C ASM)
endif()

add_library(lib_angle10 STATIC
        src/angle10.c
        include/angle10.h
)
add_library(Click.Angle10  ALIAS lib_angle10)



target_include_directories(lib_angle10 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_angle10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_angle10 PUBLIC MikroSDK.Driver)

