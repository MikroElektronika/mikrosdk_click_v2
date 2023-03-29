cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_balancer2 LANGUAGES MikroC)
else()
    project(lib_balancer2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_balancer2 STATIC
        src/balancer2.c
        include/balancer2.h
)
add_library(Click.Balancer2  ALIAS lib_balancer2)



target_include_directories(lib_balancer2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_balancer2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_balancer2 PUBLIC MikroSDK.Driver)
