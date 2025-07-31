cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum27 LANGUAGES MikroC)
else()
    project(lib_temphum27 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum27 STATIC
        src/temphum27.c
        include/temphum27.h
)
add_library(Click.TempHum27  ALIAS lib_temphum27)



target_include_directories(lib_temphum27 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum27 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum27 PUBLIC MikroSDK.Driver)

