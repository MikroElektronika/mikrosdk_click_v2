cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs232isolator LANGUAGES MikroC)
else()
    project(lib_rs232isolator LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs232isolator STATIC
        src/rs232isolator.c
        include/rs232isolator.h
)
add_library(Click.Rs232Isolator  ALIAS lib_rs232isolator)



target_include_directories(lib_rs232isolator PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs232isolator PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs232isolator PUBLIC MikroSDK.Driver)
