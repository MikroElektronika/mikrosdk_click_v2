cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum24 LANGUAGES MikroC)
else()
    project(lib_temphum24 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum24 STATIC
        src/temphum24.c
        include/temphum24.h
)
add_library(Click.TempHum24  ALIAS lib_temphum24)



target_include_directories(lib_temphum24 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum24 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum24 PUBLIC MikroSDK.Driver)

