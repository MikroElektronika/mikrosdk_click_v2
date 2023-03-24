cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_balancer5 LANGUAGES MikroC)
else()
    project(lib_balancer5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_balancer5 STATIC
        src/balancer5.c
        include/balancer5.h
)
add_library(Click.Balancer5  ALIAS lib_balancer5)



target_include_directories(lib_balancer5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_balancer5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_balancer5 PUBLIC MikroSDK.Driver)
