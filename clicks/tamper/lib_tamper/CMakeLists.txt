cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tamper LANGUAGES MikroC)
else()
    project(lib_tamper LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tamper STATIC
        src/tamper.c
        include/tamper.h
)
add_library(Click.Tamper  ALIAS lib_tamper)



target_include_directories(lib_tamper PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tamper PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tamper PUBLIC MikroSDK.Driver)
