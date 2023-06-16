cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_qirx LANGUAGES MikroC)
else()
    project(lib_qirx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_qirx STATIC
        src/qirx.c
        include/qirx.h
)
add_library(Click.QiRX  ALIAS lib_qirx)



target_include_directories(lib_qirx PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_qirx PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_qirx PUBLIC MikroSDK.Driver)
