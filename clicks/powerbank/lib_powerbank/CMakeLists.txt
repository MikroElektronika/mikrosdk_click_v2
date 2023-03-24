cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_powerbank LANGUAGES MikroC)
else()
    project(lib_powerbank LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_powerbank STATIC
        src/powerbank.c
        include/powerbank.h
)
add_library(Click.PowerBank  ALIAS lib_powerbank)



target_include_directories(lib_powerbank PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_powerbank PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_powerbank PUBLIC MikroSDK.Driver)
