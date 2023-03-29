cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irdistance LANGUAGES MikroC)
else()
    project(lib_irdistance LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irdistance STATIC
        src/irdistance.c
        include/irdistance.h
)
add_library(Click.IrDistance  ALIAS lib_irdistance)



target_include_directories(lib_irdistance PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irdistance PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irdistance PUBLIC MikroSDK.Driver)
