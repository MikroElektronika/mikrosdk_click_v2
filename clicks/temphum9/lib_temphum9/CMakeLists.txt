cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum9 LANGUAGES MikroC)
else()
    project(lib_temphum9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum9 STATIC
        src/temphum9.c
        include/temphum9.h
)
add_library(Click.TempHum9  ALIAS lib_temphum9)



target_include_directories(lib_temphum9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum9 PUBLIC MikroSDK.Driver)
