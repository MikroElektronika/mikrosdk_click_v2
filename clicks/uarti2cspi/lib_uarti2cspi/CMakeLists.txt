cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uarti2cspi LANGUAGES MikroC)
else()
    project(lib_uarti2cspi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uarti2cspi STATIC
        src/uarti2cspi.c
        include/uarti2cspi.h
)
add_library(Click.UARTI2CSPI  ALIAS lib_uarti2cspi)



target_include_directories(lib_uarti2cspi PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uarti2cspi PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uarti2cspi PUBLIC MikroSDK.Driver)
