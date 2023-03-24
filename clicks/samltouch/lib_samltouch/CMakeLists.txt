cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_samltouch LANGUAGES MikroC)
else()
    project(lib_samltouch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_samltouch STATIC
        src/samltouch.c
        include/samltouch.h
)
add_library(Click.SamlTouch  ALIAS lib_samltouch)



target_include_directories(lib_samltouch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_samltouch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_samltouch PUBLIC MikroSDK.Driver)
