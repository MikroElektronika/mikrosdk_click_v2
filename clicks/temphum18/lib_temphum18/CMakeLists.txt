cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum18 LANGUAGES MikroC)
else()
    project(lib_temphum18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum18 STATIC
        src/temphum18.c
        include/temphum18.h
)
add_library(Click.TempHum18  ALIAS lib_temphum18)



target_include_directories(lib_temphum18 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum18 PUBLIC MikroSDK.Driver)
