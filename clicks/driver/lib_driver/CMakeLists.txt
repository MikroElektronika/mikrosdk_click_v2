cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_driver LANGUAGES MikroC)
else()
    project(lib_driver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_driver STATIC
        src/driver.c
        include/driver.h
)
add_library(Click.Driver  ALIAS lib_driver)



target_include_directories(lib_driver PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_driver PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_driver PUBLIC MikroSDK.Driver)
