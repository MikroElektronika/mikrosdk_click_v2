cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dht222 LANGUAGES MikroC)
else()
    project(lib_dht222 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dht222 STATIC
        src/dht222.c
        include/dht222.h
)
add_library(Click.Dht222  ALIAS lib_dht222)



target_include_directories(lib_dht222 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dht222 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dht222 PUBLIC MikroSDK.Driver)
