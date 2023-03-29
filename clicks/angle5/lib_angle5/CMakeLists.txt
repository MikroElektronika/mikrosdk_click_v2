cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_angle5 LANGUAGES MikroC)
else()
    project(lib_angle5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_angle5 STATIC
        src/angle5.c
        include/angle5.h
)
add_library(Click.Angle5  ALIAS lib_angle5)



target_include_directories(lib_angle5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_angle5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_angle5 PUBLIC MikroSDK.Driver)
