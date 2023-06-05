cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_illuminance LANGUAGES MikroC)
else()
    project(lib_illuminance LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_illuminance STATIC
        src/illuminance.c
        include/illuminance.h
)
add_library(Click.Illuminance  ALIAS lib_illuminance)



target_include_directories(lib_illuminance PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_illuminance PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_illuminance PUBLIC MikroSDK.Driver)
