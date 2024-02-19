cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_antopwm2 LANGUAGES MikroC)
else()
    project(lib_antopwm2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_antopwm2 STATIC
        src/antopwm2.c
        include/antopwm2.h
)
add_library(Click.ANtoPWM2  ALIAS lib_antopwm2)



target_include_directories(lib_antopwm2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_antopwm2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_antopwm2 PUBLIC MikroSDK.Driver)

