cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_grideye LANGUAGES MikroC)
else()
    project(lib_grideye LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_grideye STATIC
        src/grideye.c
        include/grideye.h
)
add_library(Click.Grideye  ALIAS lib_grideye)



target_include_directories(lib_grideye PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_grideye PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_grideye PUBLIC MikroSDK.Driver)
