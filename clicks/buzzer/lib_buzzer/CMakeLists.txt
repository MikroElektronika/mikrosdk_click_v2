cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buzzer LANGUAGES MikroC)
else()
    project(lib_buzzer LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buzzer STATIC
        src/buzzer.c
        include/buzzer.h
)
add_library(Click.Buzzer  ALIAS lib_buzzer)



target_include_directories(lib_buzzer PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buzzer PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buzzer PUBLIC MikroSDK.Driver)

