cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum12 LANGUAGES MikroC)
else()
    project(lib_temphum12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum12 STATIC
        src/temphum12.c
        include/temphum12.h
)
add_library(Click.TempHum12  ALIAS lib_temphum12)



target_include_directories(lib_temphum12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum12 PUBLIC MikroSDK.Driver)
