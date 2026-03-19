cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tpspressure040my LANGUAGES MikroC)
else()
    project(lib_tpspressure040my LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tpspressure040my STATIC
        src/tpspressure040my.c
        include/tpspressure040my.h
)
add_library(Click.TPSPressure040MY  ALIAS lib_tpspressure040my)



target_include_directories(lib_tpspressure040my PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tpspressure040my PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tpspressure040my PUBLIC MikroSDK.Driver)

