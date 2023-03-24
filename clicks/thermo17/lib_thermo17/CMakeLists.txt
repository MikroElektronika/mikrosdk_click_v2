cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo17 LANGUAGES MikroC)
else()
    project(lib_thermo17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo17 STATIC
        src/thermo17.c
        include/thermo17.h
)
add_library(Click.Thermo17  ALIAS lib_thermo17)



target_include_directories(lib_thermo17 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo17 PUBLIC MikroSDK.Driver)
