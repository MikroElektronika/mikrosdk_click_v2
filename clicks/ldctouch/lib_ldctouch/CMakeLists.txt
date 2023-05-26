cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ldctouch LANGUAGES MikroC)
else()
    project(lib_ldctouch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ldctouch STATIC
        src/ldctouch.c
        include/ldctouch.h
)
add_library(Click.LDCTouch  ALIAS lib_ldctouch)



target_include_directories(lib_ldctouch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ldctouch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ldctouch PUBLIC MikroSDK.Driver)
