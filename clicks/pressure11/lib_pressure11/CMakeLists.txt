cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure11 LANGUAGES MikroC)
else()
    project(lib_pressure11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure11 STATIC
        src/pressure11.c
        include/pressure11.h
)
add_library(Click.Pressure11  ALIAS lib_pressure11)



target_include_directories(lib_pressure11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure11 PUBLIC MikroSDK.Driver)
