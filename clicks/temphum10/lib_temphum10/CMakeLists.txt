cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum10 LANGUAGES MikroC)
else()
    project(lib_temphum10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum10 STATIC
        src/temphum10.c
        include/temphum10.h
)
add_library(Click.TempHum10  ALIAS lib_temphum10)



target_include_directories(lib_temphum10 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum10 PUBLIC MikroSDK.Driver)
