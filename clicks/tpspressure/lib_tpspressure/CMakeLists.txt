cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tpspressure LANGUAGES MikroC)
else()
    project(lib_tpspressure LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tpspressure STATIC
        src/tpspressure.c
        include/tpspressure.h
)
add_library(Click.TPSPressure  ALIAS lib_tpspressure)



target_include_directories(lib_tpspressure PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tpspressure PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tpspressure PUBLIC MikroSDK.Driver)

