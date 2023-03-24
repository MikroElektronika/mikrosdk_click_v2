cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum22 LANGUAGES MikroC)
else()
    project(lib_temphum22 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum22 STATIC
        src/temphum22.c
        include/temphum22.h
)
add_library(Click.TempHum22  ALIAS lib_temphum22)



target_include_directories(lib_temphum22 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum22 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum22 PUBLIC MikroSDK.Driver)
