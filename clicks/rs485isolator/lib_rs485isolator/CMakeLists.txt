cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs485isolator LANGUAGES MikroC)
else()
    project(lib_rs485isolator LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs485isolator STATIC
        src/rs485isolator.c
        include/rs485isolator.h
)
add_library(Click.Rs485Isolator  ALIAS lib_rs485isolator)



target_include_directories(lib_rs485isolator PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs485isolator PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs485isolator PUBLIC MikroSDK.Driver)
