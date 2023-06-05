cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent825a LANGUAGES MikroC)
else()
    project(lib_hallcurrent825a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent825a STATIC
        src/hallcurrent825a.c
        include/hallcurrent825a.h
)
add_library(Click.HallCurrent825A  ALIAS lib_hallcurrent825a)



target_include_directories(lib_hallcurrent825a PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent825a PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent825a PUBLIC MikroSDK.Driver)
