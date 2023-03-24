cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nbiot LANGUAGES MikroC)
else()
    project(lib_nbiot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nbiot STATIC
        src/nbiot.c
        include/nbiot.h
)
add_library(Click.NbIot  ALIAS lib_nbiot)



target_include_directories(lib_nbiot PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nbiot PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nbiot PUBLIC MikroSDK.Driver)
