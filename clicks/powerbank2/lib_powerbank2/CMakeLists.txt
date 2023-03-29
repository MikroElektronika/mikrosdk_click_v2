cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_powerbank2 LANGUAGES MikroC)
else()
    project(lib_powerbank2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_powerbank2 STATIC
        src/powerbank2.c
        include/powerbank2.h
)
add_library(Click.Powerbank2  ALIAS lib_powerbank2)



target_include_directories(lib_powerbank2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_powerbank2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_powerbank2 PUBLIC MikroSDK.Driver)
