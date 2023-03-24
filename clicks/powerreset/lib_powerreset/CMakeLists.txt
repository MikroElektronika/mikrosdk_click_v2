cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_powerreset LANGUAGES MikroC)
else()
    project(lib_powerreset LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_powerreset STATIC
        src/powerreset.c
        include/powerreset.h
)
add_library(Click.PowerReset  ALIAS lib_powerreset)



target_include_directories(lib_powerreset PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_powerreset PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_powerreset PUBLIC MikroSDK.Driver)
