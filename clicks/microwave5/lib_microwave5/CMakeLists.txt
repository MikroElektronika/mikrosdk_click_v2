cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_microwave5 LANGUAGES MikroC)
else()
    project(lib_microwave5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_microwave5 STATIC
        src/microwave5.c
        include/microwave5.h
)
add_library(Click.Microwave5  ALIAS lib_microwave5)



target_include_directories(lib_microwave5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_microwave5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_microwave5 PUBLIC MikroSDK.Driver)

