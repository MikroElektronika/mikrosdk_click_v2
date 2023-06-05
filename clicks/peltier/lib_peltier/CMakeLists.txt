cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_peltier LANGUAGES MikroC)
else()
    project(lib_peltier LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_peltier STATIC
        src/peltier.c
        include/peltier.h
)
add_library(Click.Peltier  ALIAS lib_peltier)



target_include_directories(lib_peltier PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_peltier PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_peltier PUBLIC MikroSDK.Driver)
