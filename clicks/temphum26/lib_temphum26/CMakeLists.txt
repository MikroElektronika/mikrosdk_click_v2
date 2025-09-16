cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum26 LANGUAGES MikroC)
else()
    project(lib_temphum26 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum26 STATIC
        src/temphum26.c
        include/temphum26.h
)
add_library(Click.TempHum26  ALIAS lib_temphum26)



target_include_directories(lib_temphum26 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum26 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum26 PUBLIC MikroSDK.Driver)

