cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mux LANGUAGES MikroC)
else()
    project(lib_mux LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mux STATIC
        src/mux.c
        include/mux.h
)
add_library(Click.Mux  ALIAS lib_mux)



target_include_directories(lib_mux PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mux PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mux PUBLIC MikroSDK.Driver)
