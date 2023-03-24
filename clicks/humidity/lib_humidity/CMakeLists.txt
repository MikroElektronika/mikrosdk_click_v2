cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_humidity LANGUAGES MikroC)
else()
    project(lib_humidity LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_humidity STATIC
        src/humidity.c
        include/humidity.h
)
add_library(Click.Humidity  ALIAS lib_humidity)



target_include_directories(lib_humidity PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_humidity PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_humidity PUBLIC MikroSDK.Driver)
