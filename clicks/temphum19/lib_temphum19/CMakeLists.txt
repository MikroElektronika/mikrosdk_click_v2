cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum19 LANGUAGES MikroC)
else()
    project(lib_temphum19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum19 STATIC
        src/temphum19.c
        include/temphum19.h
)
add_library(Click.TempHum19  ALIAS lib_temphum19)



target_include_directories(lib_temphum19 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum19 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum19 PUBLIC MikroSDK.Driver)
