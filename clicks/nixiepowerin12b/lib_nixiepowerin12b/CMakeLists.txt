cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nixiepowerin12b LANGUAGES MikroC)
else()
    project(lib_nixiepowerin12b LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nixiepowerin12b STATIC
        src/nixiepowerin12b.c
        include/nixiepowerin12b.h
)
add_library(Click.NixiePowerIN12B  ALIAS lib_nixiepowerin12b)



target_include_directories(lib_nixiepowerin12b PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nixiepowerin12b PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nixiepowerin12b PUBLIC MikroSDK.Driver)

