cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs485isolator2 LANGUAGES MikroC)
else()
    project(lib_rs485isolator2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs485isolator2 STATIC
        src/rs485isolator2.c
        include/rs485isolator2.h
)
add_library(Click.Rs485Isolator2  ALIAS lib_rs485isolator2)



target_include_directories(lib_rs485isolator2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs485isolator2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs485isolator2 PUBLIC MikroSDK.Driver)
