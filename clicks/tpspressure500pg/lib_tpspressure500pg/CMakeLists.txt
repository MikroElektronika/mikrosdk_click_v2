cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tpspressure500pg LANGUAGES MikroC)
else()
    project(lib_tpspressure500pg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tpspressure500pg STATIC
        src/tpspressure500pg.c
        include/tpspressure500pg.h
)
add_library(Click.TPSPressure500PG  ALIAS lib_tpspressure500pg)



target_include_directories(lib_tpspressure500pg PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tpspressure500pg PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tpspressure500pg PUBLIC MikroSDK.Driver)

