cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vibromotor2 LANGUAGES MikroC)
else()
    project(lib_vibromotor2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vibromotor2 STATIC
        src/vibromotor2.c
        include/vibromotor2.h
)
add_library(Click.VibroMotor2  ALIAS lib_vibromotor2)



target_include_directories(lib_vibromotor2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vibromotor2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vibromotor2 PUBLIC MikroSDK.Driver)
