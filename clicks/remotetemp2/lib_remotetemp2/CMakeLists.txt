cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_remotetemp2 LANGUAGES MikroC)
else()
    project(lib_remotetemp2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_remotetemp2 STATIC
        src/remotetemp2.c
        include/remotetemp2.h
)
add_library(Click.RemoteTemp2  ALIAS lib_remotetemp2)



target_include_directories(lib_remotetemp2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_remotetemp2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_remotetemp2 PUBLIC MikroSDK.Driver)

