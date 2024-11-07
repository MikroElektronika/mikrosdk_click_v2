cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs485isolator4 LANGUAGES MikroC)
else()
    project(lib_rs485isolator4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs485isolator4 STATIC
        src/rs485isolator4.c
        include/rs485isolator4.h
)
add_library(Click.RS485Isolator4  ALIAS lib_rs485isolator4)



target_include_directories(lib_rs485isolator4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs485isolator4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs485isolator4 PUBLIC MikroSDK.Driver)

