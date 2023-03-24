cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ndirco2 LANGUAGES MikroC)
else()
    project(lib_ndirco2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ndirco2 STATIC
        src/ndirco2.c
        include/ndirco2.h
)
add_library(Click.NdirCo2  ALIAS lib_ndirco2)



target_include_directories(lib_ndirco2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ndirco2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ndirco2 PUBLIC MikroSDK.Driver)
