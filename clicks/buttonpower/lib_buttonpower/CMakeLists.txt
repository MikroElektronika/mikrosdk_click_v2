cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buttonpower LANGUAGES MikroC)
else()
    project(lib_buttonpower LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buttonpower STATIC
        src/buttonpower.c
        include/buttonpower.h
)
add_library(Click.ButtonPower  ALIAS lib_buttonpower)



target_include_directories(lib_buttonpower PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buttonpower PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buttonpower PUBLIC MikroSDK.Driver)
