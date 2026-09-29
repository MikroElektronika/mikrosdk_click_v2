cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_radiation LANGUAGES MikroC)
else()
    project(lib_radiation LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_radiation STATIC
        src/radiation.c
        include/radiation.h
)
add_library(Click.Radiation  ALIAS lib_radiation)



target_include_directories(lib_radiation PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_radiation PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_radiation PUBLIC MikroSDK.Driver)

