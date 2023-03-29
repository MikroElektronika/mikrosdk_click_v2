cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_oledw LANGUAGES MikroC)
else()
    project(lib_oledw LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_oledw STATIC
        src/oledw.c
        include/oledw.h    include/resources.h
)
add_library(Click.OLEDW  ALIAS lib_oledw)



target_include_directories(lib_oledw PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_oledw PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_oledw PUBLIC MikroSDK.Driver)
