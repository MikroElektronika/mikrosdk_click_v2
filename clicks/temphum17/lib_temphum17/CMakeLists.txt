cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum17 LANGUAGES MikroC)
else()
    project(lib_temphum17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum17 STATIC
        src/temphum17.c
        include/temphum17.h
)
add_library(Click.TempHum17  ALIAS lib_temphum17)



target_include_directories(lib_temphum17 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum17 PUBLIC MikroSDK.Driver)
