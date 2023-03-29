cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum14 LANGUAGES MikroC)
else()
    project(lib_temphum14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum14 STATIC
        src/temphum14.c
        include/temphum14.h
)
add_library(Click.TempHum14  ALIAS lib_temphum14)



target_include_directories(lib_temphum14 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum14 PUBLIC MikroSDK.Driver)
