cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_remotetemp3 LANGUAGES MikroC)
else()
    project(lib_remotetemp3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_remotetemp3 STATIC
        src/remotetemp3.c
        include/remotetemp3.h
)
add_library(Click.RemoteTemp3  ALIAS lib_remotetemp3)



target_include_directories(lib_remotetemp3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_remotetemp3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_remotetemp3 PUBLIC MikroSDK.Driver)

