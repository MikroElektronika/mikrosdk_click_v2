cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_g2c3g LANGUAGES MikroC)
else()
    project(lib_g2c3g LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_g2c3g STATIC
        src/g2c3g.c
        include/g2c3g.h
)
add_library(Click.G2C3G  ALIAS lib_g2c3g)



target_include_directories(lib_g2c3g PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_g2c3g PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_g2c3g PUBLIC MikroSDK.Driver)

