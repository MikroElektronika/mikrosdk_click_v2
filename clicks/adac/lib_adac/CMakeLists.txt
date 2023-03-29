cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_adac LANGUAGES MikroC)
else()
    project(lib_adac LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_adac STATIC
        src/adac.c
        include/adac.h
)
add_library(Click.ADAC  ALIAS lib_adac)



target_include_directories(lib_adac PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_adac PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_adac PUBLIC MikroSDK.Driver)
