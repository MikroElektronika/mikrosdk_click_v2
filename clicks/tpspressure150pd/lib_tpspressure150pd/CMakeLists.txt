cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tpspressure150pd LANGUAGES MikroC)
else()
    project(lib_tpspressure150pd LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tpspressure150pd STATIC
        src/tpspressure150pd.c
        include/tpspressure150pd.h
)
add_library(Click.TPSPressure150PD  ALIAS lib_tpspressure150pd)



target_include_directories(lib_tpspressure150pd PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tpspressure150pd PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tpspressure150pd PUBLIC MikroSDK.Driver)

