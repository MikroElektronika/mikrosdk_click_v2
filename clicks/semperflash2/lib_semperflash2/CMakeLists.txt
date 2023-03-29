cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_semperflash2 LANGUAGES MikroC)
else()
    project(lib_semperflash2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_semperflash2 STATIC
        src/semperflash2.c
        include/semperflash2.h
)
add_library(Click.SemperFlash2  ALIAS lib_semperflash2)



target_include_directories(lib_semperflash2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_semperflash2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_semperflash2 PUBLIC MikroSDK.Driver)
