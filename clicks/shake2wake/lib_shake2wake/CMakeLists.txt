cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_shake2wake LANGUAGES MikroC)
else()
    project(lib_shake2wake LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_shake2wake STATIC
        src/shake2wake.c
        include/shake2wake.h
)
add_library(Click.Shake2Wake  ALIAS lib_shake2wake)



target_include_directories(lib_shake2wake PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_shake2wake PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_shake2wake PUBLIC MikroSDK.Driver)
