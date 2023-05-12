cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_battmon4 LANGUAGES MikroC)
else()
    project(lib_battmon4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_battmon4 STATIC
        src/battmon4.c
        include/battmon4.h
)
add_library(Click.BATTMON4  ALIAS lib_battmon4)



target_include_directories(lib_battmon4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_battmon4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_battmon4 PUBLIC MikroSDK.Driver)
