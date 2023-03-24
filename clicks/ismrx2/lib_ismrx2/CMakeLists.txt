cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ismrx2 LANGUAGES MikroC)
else()
    project(lib_ismrx2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ismrx2 STATIC
        src/ismrx2.c
        include/ismrx2.h
)
add_library(Click.ISMRX2  ALIAS lib_ismrx2)



target_include_directories(lib_ismrx2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ismrx2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ismrx2 PUBLIC MikroSDK.Driver)

