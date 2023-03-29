cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c4glteatt LANGUAGES MikroC)
else()
    project(lib_c4glteatt LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c4glteatt STATIC
        src/c4glteatt.c
        include/c4glteatt.h
)
add_library(Click.4GLTEATT  ALIAS lib_c4glteatt)



target_include_directories(lib_c4glteatt PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c4glteatt PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c4glteatt PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c4glteatt PUBLIC MikroSDK.Conversions)
