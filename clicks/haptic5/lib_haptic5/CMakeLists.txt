cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_haptic5 LANGUAGES MikroC)
else()
    project(lib_haptic5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_haptic5 STATIC
        src/haptic5.c
        include/haptic5.h
)
add_library(Click.Haptic5  ALIAS lib_haptic5)



target_include_directories(lib_haptic5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_haptic5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_haptic5 PUBLIC MikroSDK.Driver)

