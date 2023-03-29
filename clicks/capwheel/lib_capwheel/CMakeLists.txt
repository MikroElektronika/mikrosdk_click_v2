cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_capwheel LANGUAGES MikroC)
else()
    project(lib_capwheel LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_capwheel STATIC
        src/capwheel.c
        include/capwheel.h
)
add_library(Click.CapWheel  ALIAS lib_capwheel)



target_include_directories(lib_capwheel PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_capwheel PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_capwheel PUBLIC MikroSDK.Driver)
