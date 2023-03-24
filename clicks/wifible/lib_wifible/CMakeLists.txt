cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_wifible LANGUAGES MikroC)
else()
    project(lib_wifible LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_wifible STATIC
        src/wifible.c
        include/wifible.h
)
add_library(Click.WifiBle  ALIAS lib_wifible)



target_include_directories(lib_wifible PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_wifible PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_wifible PUBLIC MikroSDK.Driver)
