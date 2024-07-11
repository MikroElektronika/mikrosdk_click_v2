cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum25 LANGUAGES MikroC)
else()
    project(lib_temphum25 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum25 STATIC
        src/temphum25.c
        include/temphum25.h
)
add_library(Click.TempHum25  ALIAS lib_temphum25)



target_include_directories(lib_temphum25 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum25 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum25 PUBLIC MikroSDK.Driver)

