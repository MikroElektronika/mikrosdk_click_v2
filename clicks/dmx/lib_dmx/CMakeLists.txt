cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dmx LANGUAGES MikroC)
else()
    project(lib_dmx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dmx STATIC
        src/dmx.c
        include/dmx.h
)
add_library(Click.Dmx  ALIAS lib_dmx)



target_include_directories(lib_dmx PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dmx PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dmx PUBLIC MikroSDK.Driver)
