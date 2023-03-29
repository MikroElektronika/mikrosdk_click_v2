cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_macaddress LANGUAGES MikroC)
else()
    project(lib_macaddress LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_macaddress STATIC
        src/macaddress.c
        include/macaddress.h
)
add_library(Click.MacAddress  ALIAS lib_macaddress)



target_include_directories(lib_macaddress PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_macaddress PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_macaddress PUBLIC MikroSDK.Driver)
