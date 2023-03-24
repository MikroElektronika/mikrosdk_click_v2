cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum16 LANGUAGES MikroC)
else()
    project(lib_temphum16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum16 STATIC
        src/temphum16.c
        include/temphum16.h
)
add_library(Click.TempHum16  ALIAS lib_temphum16)



target_include_directories(lib_temphum16 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum16 PUBLIC MikroSDK.Driver)
