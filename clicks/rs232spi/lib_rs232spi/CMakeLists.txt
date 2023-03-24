cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs232spi LANGUAGES MikroC)
else()
    project(lib_rs232spi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs232spi STATIC
        src/rs232spi.c
        include/rs232spi.h
)
add_library(Click.Rs232Spi  ALIAS lib_rs232spi)



target_include_directories(lib_rs232spi PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs232spi PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs232spi PUBLIC MikroSDK.Driver)
