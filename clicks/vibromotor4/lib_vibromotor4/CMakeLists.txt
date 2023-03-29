cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vibromotor4 LANGUAGES MikroC)
else()
    project(lib_vibromotor4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vibromotor4 STATIC
        src/vibromotor4.c
        include/vibromotor4.h
)
add_library(Click.VibroMotor4  ALIAS lib_vibromotor4)



target_include_directories(lib_vibromotor4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vibromotor4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vibromotor4 PUBLIC MikroSDK.Driver)
