cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum4 LANGUAGES MikroC)
else()
    project(lib_temphum4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum4 STATIC
        src/temphum4.c
        include/temphum4.h
)
add_library(Click.TempHum4  ALIAS lib_temphum4)



target_include_directories(lib_temphum4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum4 PUBLIC MikroSDK.Driver)
