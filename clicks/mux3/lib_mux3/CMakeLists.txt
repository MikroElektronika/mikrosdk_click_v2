cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mux3 LANGUAGES MikroC)
else()
    project(lib_mux3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mux3 STATIC
        src/mux3.c
        include/mux3.h
)
add_library(Click.Mux3  ALIAS lib_mux3)



target_include_directories(lib_mux3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mux3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mux3 PUBLIC MikroSDK.Driver)
