cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum7 LANGUAGES MikroC)
else()
    project(lib_temphum7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum7 STATIC
        src/temphum7.c
        include/temphum7.h
)
add_library(Click.TempHum7  ALIAS lib_temphum7)



target_include_directories(lib_temphum7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum7 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(lib_temphum7 PUBLIC MikroSDK.Board)
