cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vibromotor LANGUAGES MikroC)
else()
    project(lib_vibromotor LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vibromotor STATIC
        src/vibromotor.c
        include/vibromotor.h
)
add_library(Click.VibroMotor  ALIAS lib_vibromotor)



target_include_directories(lib_vibromotor PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vibromotor PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vibromotor PUBLIC MikroSDK.Driver)
