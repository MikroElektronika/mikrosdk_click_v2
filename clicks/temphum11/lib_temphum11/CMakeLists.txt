cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum11 LANGUAGES MikroC)
else()
    project(lib_temphum11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum11 STATIC
        src/temphum11.c
        include/temphum11.h
)
add_library(Click.TempHum11  ALIAS lib_temphum11)



target_include_directories(lib_temphum11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum11 PUBLIC MikroSDK.Driver)
